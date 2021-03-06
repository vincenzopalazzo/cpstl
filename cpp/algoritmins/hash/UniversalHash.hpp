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
  T value_a = -1;
  T value_b = -1;
  std::size_t size;
  long long prime;

  void make_random_choice() {
    std::random_device rd;
    std::mt19937_64 mt(rd());
    auto generator = std::uniform_int_distribution<T>(1, this->prime - 1);
    this->value_a = generator(mt);
    generator = std::uniform_int_distribution<T>(0, this->prime - 1);
    this->value_b = generator(mt);
    std::cout << "Value A " << this->value_a << "\n";
    std::cout << "Value B " << this->value_b << "\n";
  }

  /**
   * Naive method to chose the random number from m to 2m.
   *
   * Move this logic out of this class and also implement this algorithm
   * to find the prime number in ad efficient way
   * https://en.wikipedia.org/wiki/Sieve_of_Atkin
   * @return -1 if there are any random number of the first prime number
   */
  T generate_prime_number(T number) {
    assert(number > 0);
    for (T p = number + 1; p <= (2 * number) + 1; p++) {
      auto isPrime = true;
      for (T i = 2; i < std::sqrt(p); i++) {
        if (p % i == 0) {
          isPrime = false;
          break;
        }
      }
      if (isPrime) return p;
    }
    assert(false && "Prime number not found");
  }

 public:
  UniversalHash() {}
  UniversalHash(std::size_t size) : size(size) {
    this->prime = generate_prime_number(size);
    make_random_choice();
    //std::cout << "---------------------\n";
    //std::cout << this->value_a << " " << this->value_b << " " << this->prime
    //          << " " << this->size << "\n";
  }

  T universal_hashing(T to_hash) {
    assert(this->value_a >= 0 && this->value_b >= 0);
    return ((this->value_a * to_hash + this->value_b) % this->prime) %
           this->size;
  }
};
};  // namespace cpstl
