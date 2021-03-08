/**
 * Perfect Hash function C++ implementation
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
#ifndef PERFECTHASH_T
#define PERFECTHASH_T

#include <cassert>
#include <map>

#include "UniversalHash.hpp"

namespace cpstl {
template <class T>
class PerfectHash {
 private:
  cpstl::UniversalHash<T> universal_hash;
  cpstl::UniversalHash<T> second_universal_hash;
  std::size_t size;
  std::map<T, std::vector<T>> first_level;
  std::map<T, std::vector<T>> fix_bucket;

  /**
   * Add more information about this method
   */
  void perfect_hash(T to_hash) {
    auto hash_value = this->universal_hash.universal_hashing(to_hash);
    auto elem_at = first_level.find(hash_value);
    if (elem_at != first_level.end()) {
      auto &list = first_level.at(hash_value);
      list.push_back(to_hash);
      return;
    }
    std::vector<T> values{to_hash};
    first_level.emplace(hash_value, values);
  }

  /*
   * This method is ran after the insert operation to remove the
   * Collision found during the insert with the first hash function.
   *
   * Question: How I can retrieval the information in the second bucket if
   * these information are generated with a random function choose at runtime?
   * The possibility to store the hash function increase the complexity to O(H)
   * in the worst case.
   *
   * Question: The rebuild operation how is write now create a lot of collision,
   * also with the python code, can be the problem the algorithm to choose the
   * prime number?.
   *
   * FIXME(vincenzopalazzo): This method is buggy
   */
  bool rebalance_bucket() {
    for (auto buck_elem : this->first_level) {
      auto size_collision = buck_elem.second.size();
      auto size_new_bucket = size_collision * size_collision;
      this->second_universal_hash.new_hash_function(size_new_bucket);
      for (auto in_bucket : buck_elem.second) {
        auto new_hash =
            this->second_universal_hash.universal_hashing(in_bucket);
        auto prev_hash = buck_elem.first;
        auto fixet_at = this->fix_bucket.find(prev_hash);
        if (fixet_at != this->fix_bucket.end()) {
          auto &new_bucket = this->fix_bucket.at(prev_hash);
          if (new_bucket[new_hash] == std::numeric_limits<T>::min()) {
            new_bucket[new_hash] = in_bucket;
          } else {
            std::cout << "-------- COLLISION DETECTED -----------\n";
            return false;
          }
        } else {
          std::cout << new_hash << "\n";
          std::vector<T> new_bucket(size_new_bucket + 2,
                                    std::numeric_limits<T>::min());
          auto &elem = new_bucket.at(new_hash);
          elem = in_bucket;
          this->fix_bucket.emplace(prev_hash, new_bucket);
        }
      }
    }
    return true;
  }

 public:
  PerfectHash(std::size_t size)
      : size(2 * size),
        universal_hash(2 * size),
        second_universal_hash(2 * size) {}

  void insert_list(std::vector<T> to_insert) {
    for (auto elem : to_insert) {
      this->perfect_hash(elem);
    }
    auto finish = this->rebalance_bucket();
    while (!finish) finish = this->rebalance_bucket();
  }

  std::map<T, std::vector<T>> get_bucket() { return this->fix_bucket; }

  T get_element(T key) { assert(false && "Not supported yet"); }
};
};  // namespace cpstl
#endif
