/**
 * CPSTL demo to use the TestTool method to make simple test unit
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
#include <cstdlib>

#include "../BloomFilter.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

using namespace std;

void TEST_BLOOM_FILTER_ONE() {
  std::vector<int> inputs = {11, 25, 36, 41, 57, 66, 73, 89, 95};
  cpstl::BloomFilter<int> bloomFilter(inputs.size());
  for (auto elem : inputs) {
    bloomFilter.insert(elem);
  }
  auto findAll = true;
  for (auto elem : inputs) {
    auto result = bloomFilter.contains(elem);
    if (result == false) {
      findAll = false;
      break;
    }
  }
  cpstl::assert_is_true("TEST_BLOOM_FILTER_ONE", findAll);
}

void TEST_BLOOM_FILTER_TWO() {
  std::vector<int> inputs = {11, 25, 36, 41, 57, 66, 73, 89, 95};
  cpstl::BloomFilter<int> bloomFilter(inputs.size());
  for (auto elem : inputs) {
    bloomFilter.insert(elem);
  }
  std::vector<int> notInside = {234, 212, 323, 22, 21};
  auto falsePositive = false;
  for (auto elem : notInside) {
    auto result = bloomFilter.contains(elem);
    if (result == true) {
      falsePositive = true;
      break;
    }
  }
  cpstl::assert_is_true("TEST_BLOOM_FILTER_TWO", !falsePositive);
}

int main() {
  TEST_BLOOM_FILTER_ONE();
  TEST_BLOOM_FILTER_TWO();
  return EXIT_SUCCESS;
}
