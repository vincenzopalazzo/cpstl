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

namespace cpstl {
  class InvertedIndex {
  private:
    std::map<std::string, std::vector<std::size_t>> posting_list;
    std::set<std::string> files_name;

    /**
     * Load the file with the file_path, and fill the posting_list
     * with the information found in the file.
     * This method should take care to remove all the not word content,
     * like comma, dots, ecc.
     */
    void make_posting_list_for_file(std::string const &file_path) { }

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
