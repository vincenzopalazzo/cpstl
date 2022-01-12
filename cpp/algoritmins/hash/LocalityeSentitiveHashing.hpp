/**
 * Locality Sensitive Hashing C++ implementation
 * Copyright (C) 2020-2021  Vincenzo Palazzo vincenzopalazzodev@gmail.com
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
#ifndef LSH_HPP
#define LSH_HPP

// Reference implementation https://github.com/gamboviol/lsh/blob/master/lsh.py
namespace cpstl {
/**
 * Locality Sensitive Hashing C++ implementation.
 *
 * author: https://github.com/vincenzopalazzo
 */
class LocalitySensitiveHashing {
 public:
  /**
   * Make a comparison between two key, and return true if it is similar,
   * otherwise false.
   */
  bool are_similar(std::string const &key1, std::string const &key2) const {
    return false;
  }

  /**
   * Make the hash of one key in according with the hash
   * function choose.
   */
  int64_t hash(std::string const &key) const { return 0; }
};
};  // namespace cpstl

#endif
