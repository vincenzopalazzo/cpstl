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
#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "UniversalHash.hpp"

namespace cpstl {

template <class T>
class BloomFilter {
 private:
  // Default value, for the motivation of this default value
  // tale in consideration to run the benchmarks and see the result.
  const std::size_t filter_factor = 2;
  std::size_t size;
  std::vector<uint8_t> filter;
  std::vector<cpstl::UniversalHash<T>> hash_functions;

  std::size_t calculate_number_of_hash_function(std::size_t filter_factor,
                                                std::size_t size) {
    return (std::log(2) * ((filter_factor * size) / size));
  }

 public:
  BloomFilter(std::size_t size, std::size_t factor) :
    filter(factor * size, 0) {
    this->size = size;
    auto optimal_hash_size =
        this->calculate_number_of_hash_function(factor, size);
    this->hash_functions = std::vector<cpstl::UniversalHash<T>>(
        optimal_hash_size, cpstl::UniversalHash<T>(factor * this->size));
  }

  BloomFilter(std::size_t size) {
    BloomFilter(size, filter_factor);
  }

  void insert(T value) {
    for (auto hash : hash_functions) {
      auto pos = hash.universal_hashing(value);
      filter[pos] = true;
    }
  }

  bool contains(T value) {
    for (auto hash : hash_functions) {
      auto pos = hash.universal_hashing(value);
      if (filter[pos] == false) return false;
    }
    return true;
  }
};
};  // namespace cpstl
#endif
