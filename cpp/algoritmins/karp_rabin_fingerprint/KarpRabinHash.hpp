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
#include <cstring>
#include <iostream>
#include <vector>

namespace cpstl {

template <class T>
class KarpRabinHash {
 private:
  std::vector<int> prime_numbers = {62563, 62581, 62591, 62597, 62603,
                                    62617, 62627, 62633, 62639, 62653};

  long long prime_number;

  std::vector<unsigned char> string_to_to_bytes(std::string value) {
    return std::vector<unsigned char>(value.begin(), value.end());
  }

 public:
  KarpRabinHash() {
    auto random_pos = std::rand() % (prime_numbers.size() - 1);
    prime_number = prime_numbers.at(random_pos);
  }

  T hash(std::string value) {
    auto vector_bytes = string_to_to_bytes(value);
    // x' = ((x « 1) + bit[i]) % p
    for (std::size_t i = 1; i < vector_bytes.size(); i++) {
      vector_bytes[i] = (vector_bytes[i - 1] + vector_bytes[i]) % prime_number;
    }
    return vector_bytes.back();
  }
};
};  // namespace cpstl
