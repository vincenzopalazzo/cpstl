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

/**
 * It is used to calculate the number of
 * hash function to use inside the bloom filter.
 *
 * This number are from this chart
 * https://freecontent.manning.com/wp-content/uploads/bloom-filters_06.png
 */
enum class ErrProb { HIGHT = 6, MEDIUM = 10, LOW = 14 };

template <class T>
class BloomFilter {
 private:
  std::size_t size;
  std::vector<uint8_t> filter;
  std::vector<cpstl::UniversalHash<T>> hash_functions;

  uint16_t from_enum_to_prob(ErrProb prob) {
    switch (prob) {
      case ErrProb::HIGHT:
        return 6;
      case ErrProb::MEDIUM:
        return 10;
      case ErrProb::LOW:
        return 16;
    }
    assert(false && "Error probability unknown");
  }

  std::size_t calculate_number_of_hash_function(uint16_t filter_factor,
                                                std::size_t size) {
    return (std::log(2) * ((filter_factor * size / size)));
  }

 public:
  BloomFilter(std::size_t size, ErrProb err_pro = ErrProb::MEDIUM) {
    this->size = size;
    auto factor = from_enum_to_prob(err_pro);
    filter = std::vector<uint8_t>(factor * size, 0);
    auto optimal_hash_size =
        this->calculate_number_of_hash_function(factor, size);
    this->hash_functions = std::vector<cpstl::UniversalHash<T>>(
        optimal_hash_size, cpstl::UniversalHash<T>(factor * this->size));
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
