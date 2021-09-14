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
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>

namespace cpstl {

  namespace internal {
    class PostingItem {
    public:
      std::name_file;
      std::size_t count;
    };
  };

  class InvertedIndex {
  private:
    // What if we include an hash of the word and not the word here?
    // maybe in another implementation.
    std::map<std::string, std::vector<PostingItem>> posting_list;
    std::set<std::string> files_name;

    // we need to add a vector for each new file
    // maybe here it is better use an internal class
    void add_word(std::string const &word, bool &is_fist) { }

    // A word can contains space somewhere, or also
    // symbols. With this method we make a cleaning of the word.
    void clean_word(std::string &word) { }

    void parsing_line(std::string &line) {
      // We avoid to use stringstream because it is slow and
      // we use the following approach https://stackoverflow.com/a/236153/10854225
      std::string::size_type prev_pos = 0, pos = 0;
      // we find the position of the next space
      while((pos = line.find(' ', pos)) != std::string::npos){
        // We get the string from th pos - prev_pos to get the new word
        std::string word(line.substr(prev_pos, pos - prev_pos));
        // Log the word here
        clean_word(word);
        add_word(word);
        // Before we increment the position and after
        // we will return continue with the execution.
        prev_pos = ++pos;
      }

      // we extract the last line.
      std::string last_word(line.substr(prev_pos, pos - prev_pos));
      clean_word(last_word);
      add_word(last_word);
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
        parsing_line(line);
    }

  public:
    bool add_file(std::string const &file_path) {

      // check if the file is already added
      if (files_name.find(file_path) != files_name.end())
        return false;

      files_name.insert(file_path);

      make_posting_list_for_file(file_path);

      return true;
    }

    std::vector<std::string> and_query(std::string const &word_a,
                                       std::string const &word_b) {
      return std::vector<std::string>();
    }
  };
};

#endif
