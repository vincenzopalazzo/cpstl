/**
 * Universal Hash function C++ implementation
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
#ifndef CUCKOOHASHING_H
#define CUCKOOHASHING_H

#include <map>

#include "UniversalHash.hpp"

namespace cpstl {
template <typename T>
class CuckooHashing {
 private:
  cpstl::UniversalHash<T> hash_function_one;
  cpstl::UniversalHash<T> hash_function_twoo;
  std::map<T, T> bucket;
  std::size_t size;

  void rebuild() {
    hash_function_one.new_hash_function(2 * this->size);
    hash_function_twoo.new_hash_function(2 * this->size);
    std::vector<T> values;
    values.reserve(this->bucket.size());
    for (auto value : this->bucket) {
      values.push_back(value.second);
    }
    this->bucket.clear();
    for (auto elem : values) this->insert(elem);
  }

 public:
  CuckooHashing(std::size_t size)
      : size(size), hash_function_one(2 * size), hash_function_twoo(2 * size) {}

  void insert(T key) {
    auto first_value = this->hash_function_one.universal_hashing(key);
    auto second_value = this->hash_function_twoo.universal_hashing(key);
    auto exist_on_one = this->bucket.find(first_value);
    auto exist_on_two = this->bucket.find(second_value);
    auto exist = false;
    if (exist_on_one != this->bucket.end()) {
      auto elem = exist_on_one->second;
      exist = (elem == key);
    }
    if (exist == false && exist_on_two != this->bucket.end()) {
      auto elem = exist_on_two->second;
      exist = (elem == key);
    }
    if (exist == true) return;

    // Walk in the path to find a place for the table
    auto pos = first_value;
    for (std::size_t i = 0; i < this->bucket.size() + 1; i++) {
      auto elem = this->bucket.find(pos);
      if (elem == this->bucket.end()) {
        this->bucket.insert(std::pair<T, T>(pos, key));
        return;
      }
      // Swap position
      auto tmp = bucket[pos];
      bucket[pos] = key;
      key = tmp;
      // std::swap(value, bucket[pos]); // Exchange position
      auto hash_one = this->hash_function_one.universal_hashing(key);
      auto hash_two = this->hash_function_twoo.universal_hashing(key);
      if (pos == hash_one)
        pos = hash_two;
      else
        pos = hash_one;
    }
    // std::cout << "Rebuild---\n";
    this->rebuild();
    this->insert(key);
  }

  bool at(T key) {
    auto hash_one = this->hash_function_one.universal_hashing(key);
    auto hash_two = this->hash_function_twoo.universal_hashing(key);
    auto elem = this->bucket.find(hash_one);
    if (elem != this->bucket.end() && elem->second == key) {
      return true;
    }
    return this->bucket.find(hash_two)->second == key;
  }
};
};  // namespace cpstl

#endif
