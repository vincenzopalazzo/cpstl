/**
 * Red and Black Tree data structure C++ implementation
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
#include <cmath>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

namespace cpstl {
template <class T>
class UniversalHash {
 private:
  std::random_device rd;
  long value_a;
  long value_b;
  std::size_t size;
  long prime;

  void make_random_choice() {
    std::mt19937 mt(rd());
    // TODO: It is really necessary use two make the function uniform_int_distribution?
    auto generator = std::uniform_int_distribution<int>(1, this->prime - 1);
    this->value_a = generator(mt);
    generator = std::uniform_int_distribution<int>(0, this->prime - 1);
    this->value_b = generator(mt);
  }
  /**
   * Naive method to chose the random number from m to 2m
   * @return -1 if there are any random number of the first prime number
   */
  T generate_prime_number(T number) {
    assert(number > 0);
    for (auto p = number + 1; p <= (2 * number); p++) {
      for (auto i = 2; i < std::sqrt(p); i++) {
        if (i % 2 == 0) return p;
      }
    }
    return -1;
  }

 public:
  UniversalHash(size_t size) : size(size) {
    this->prime = generate_prime_number(size);
    make_random_choice();
  }

  T universal_hashing(long to_hash) {
    return (((this->value_a * to_hash) + this->value_b) % this->prime) %
           this->size;
  }
};
};  // namespace cpstl
