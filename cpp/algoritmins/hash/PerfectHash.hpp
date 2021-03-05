/**
 * Perfect Hash function C++ implementation
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
#include <cassert>
#include <map>

#include "UniversalHash.hpp"

namespace cpstl {
template <class T>
class PerfectHash {
 private:
  cpstl::UniversalHash<T> universal_hash;
  std::size_t size;
  std::map<T, std::vector<T>> first_level;
  std::map<T, T> fix_bucket;

  /**
   * Add more information about this method
   */
  void perfect_hash(T to_hash) {
    auto hash_value = this->universal_hash.universal_hashing(to_hash);
    if (first_level.find(hash_value) != first_level.end()) {
      auto &list = first_level.at(hash_value);
      list.push_back(to_hash);
      return;
    }
    std::vector<T> values = {to_hash};
    first_level.emplace(hash_value, values);
  }

  /*
   * TODO: add more information about this method
   *
   * FIXME(vincenzopalazzo): This method is buggy
   */
  void rebalance_bucket() {
    for (auto buck_elem : this->first_level) {
      if (buck_elem.second.size() > 1) {
        auto size_collision = buck_elem.second.size();
        cpstl::UniversalHash<T> fix_universal_hash(size_collision *
                                                   size_collision);
        for (auto elem : buck_elem.second) {
          auto fix_hash_value = fix_universal_hash.universal_hashing(elem);
          std::cout << fix_hash_value << "\n";
          if (this->fix_bucket.find(fix_hash_value) != this->fix_bucket.end()) {
            // assert(false && "Collision detected");
            // a possible operation can be
            std::cout << "******** Collision detected *******\n";
            this->fix_bucket.clear();
            rebalance_bucket();
          }
          this->fix_bucket.emplace(fix_hash_value, elem);
        }
      } /* else if (!buck_elem.second.empty()) {
         // I'm sure that there is only one element
         auto elem = buck_elem.second[0];
         auto hash_value = this->fix_universal_hash.universal_hashing(elem);
         this->fix_bucket.emplace(hash_value, elem);
         }*/
    }
  }

 public:
  PerfectHash(std::size_t size) : size(2 * size), universal_hash(2 * size) {}

  void insert_list(std::vector<T> to_insert) {
    for (auto elem : to_insert) {
      this->perfect_hash(elem);
    }
    this->rebalance_bucket();
  }

  std::map<T, T> get_bucket() { return this->fix_bucket; }

  T get_element(T key) { assert(false && "Not supported yet"); }
};
};  // namespace cpstl
