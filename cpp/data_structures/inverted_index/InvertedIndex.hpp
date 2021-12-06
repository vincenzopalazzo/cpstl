/**
 * Bloom Filter with Universal Hashing C++ implementation
 * Copyright (C) 2020  Vincenzo Palazzo vincenzopalazzodev@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */
#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <vector>
#include <map>
#include <set>
#include <memory>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <iostream>
#include <functional>

#include "UniversalHash.hpp"


namespace cpstl {

  class InvertedIndex;

  namespace internal {

    class PostingPair;

    class PostingItem {
    private:
      std::string name_file;
      std::size_t count;

      friend InvertedIndex;
      friend PostingPair;
    public:
      PostingItem() {}

      PostingItem(std::string const &name_file, std::size_t count):
        name_file(name_file), count(count) {}

      void increment_occurence(std::size_t increment = 1) {
        this->count += increment;
      }
    };

    class PostingPair {
    private:
      std::shared_ptr<UniversalHash<int>> hash_function;
      int hash_file;
      // TODO: override this with only an occurrence?
      PostingItem posting_item;

      friend PostingItem;
      friend InvertedIndex;

    public:
      PostingPair() { }

      PostingPair(std::string const &name_file, std::shared_ptr<UniversalHash<int>> hash_function): hash_function(hash_function) {
        this->posting_item = PostingItem(name_file, 1);
        this->hash_file = this->hash_function->universal_hashing(name_file);
      }

      bool find(std::string const &key) {
        assert (key == posting_item.name_file);
        return hash_file == hash_function->universal_hashing(key);
      }

      void increment_occurence(std::size_t increment = 1) {
        posting_item.increment_occurence(increment);
      }
    };
  };

  class InvertedIndex {
  private:
    // What if we include an hash of the word and not the word here?
    // maybe in another implementation.
    std::map<std::string, std::vector<internal::PostingPair>> posting_list;
    std::set<std::string> files_name;
    std::size_t def_size = 40000;
    std::shared_ptr<UniversalHash<int>> hash_function;

    // we need to add a vector for each new file
    // maybe here it is better use an internal class
    void add_word(std::string const &name_file, std::string const &word) {
      if (posting_list.find(word) != posting_list.end()) {
        auto list = posting_list[word];
        for (auto &file_record : list) {
          if (file_record.find(name_file)) {
            file_record.increment_occurence();
            return;
          }
        }
      }
      posting_list.insert(std::make_pair(word, std::vector<internal::PostingPair>{internal::PostingPair(name_file, hash_function)}));
    }

    // A word can contains space somewhere, or also
    // symbols. With this method we make a cleaning of the word.
    void clean_word(std::string &word) { }

    void parsing_line(std::string const &name_file, std::string &line) {
      // We avoid to use stringstream because it is slow and
      // we use the following approach https://stackoverflow.com/a/236153/10854225
      std::string::size_type prev_pos = 0, pos = 0;
      // we find the position of the next space
      while((pos = line.find(' ', pos)) != std::string::npos){
        // We get the string from th pos - prev_pos to get the new word
        std::string word(line.substr(prev_pos, pos - prev_pos));
        // Log the word here
        clean_word(word);
        add_word(name_file, word);
        // Before we increment the position and after
        // we will return continue with the execution.
        prev_pos = ++pos;
      }

      // we extract the last line.
      std::string last_word(line.substr(prev_pos, pos - prev_pos));
      clean_word(last_word);
      add_word(name_file, last_word);
    }

    /**
     * Load the file with the file_path, and fill the posting_list
     * with the information found in the file.
     * This method should take care to remove all the not word content,
     * like comma, dots, ecc.
     */
    void make_posting_list_for_file(std::string const &file_path) {
      // from the following stackoverflow post
      // https://stackoverflow.com/a/47829709/10854225
      std::ifstream stream;
      stream.open(file_path);
      assert(stream.is_open());
      std::string line;
      while(stream.good() && getline(stream, line))
        parsing_line(file_path, line);
    }

  public:

    InvertedIndex() {
      this->hash_function = std::make_shared<UniversalHash<int>>(def_size);
    }


    bool add_file(std::string const &file_path) {

      // check if the file is already added
      if (files_name.find(file_path) != files_name.end())
        return false;

      files_name.insert(file_path);

      make_posting_list_for_file(file_path);

      return true;
    }

    std::string to_string() {
      std::string table = "";
      auto posting_iter = posting_list.begin();
      for (std::size_t index = 0; index < posting_list.size(); index++) {
        std::string row = posting_iter->first +  ":\t\t";

        for (auto &file_record : posting_iter->second) {
          row += "| " + file_record.posting_item.name_file + ": " + std::to_string(file_record.posting_item.count) + "\n";
        }
        table += row;

        posting_iter++;
      }
      return table;
    }

    std::vector<std::string> and_query(std::string const &word_a,
                                       std::string const &word_b) {
      return std::vector<std::string>();
    }
  };
};

#endif
