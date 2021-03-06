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

#include "../CuckooHashing.hpp"
#include "../PerfectHash.hpp"
#include "../UniversalHash.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

using namespace std;

const cpstl::Log LOG(false);

/**
 * This test work on probability that the UniversalHash function
 * choosen work well for the input array, but this is not true for
 * each iteration. It can happen that sometime we can have a collision.
 *
 * This could be problem an it is managed with an implementation called
 * perferc hasing.
 */
void TEST_CASE_ONE() {
  std::vector<int> inputs = {11, 25, 36, 41, 57, 66, 73, 89, 95};
  cpstl::UniversalHash<long> universal_hash(inputs.size());
  std::map<long, std::vector<long>> set;
  for (auto elem : inputs) {
    auto hash = universal_hash.universal_hashing(elem);
    if (set.find(hash) != set.end()) {
      auto& list = set.at(hash);
      list.push_back(hash);
    } else {
      std::vector<long> new_vector;
      new_vector.push_back(hash);
      set.insert(std::pair<long, std::vector<long>>(hash, new_vector));
    }
  }
  auto collision = set.size() == inputs.size();
  for (auto elem : inputs) {
    auto hash = universal_hash.universal_hashing(elem);
    auto list = set.at(hash);
    if (list.size() > 1) cpstl::cp_log(LOG, "\t --- Collision detected ---");
    cpstl::cp_log(LOG, "\tValue " + std::to_string(elem) + " with hash " +
                           std::to_string(hash));
    cpstl::cp_log(LOG, list);
  }
  cpstl::assert_is_true("TEST_CASE_ONE", !collision);
  cpstl::cp_log(LOG, inputs);
}

void TEST_CASE_ONE_PERFECT_HASH() {
  std::vector<int> inputs = {11, 25, 36, 41, 57, 66, 73, 89, 95};
  cpstl::PerfectHash<int> perfect_map(inputs.size());
  perfect_map.insert_list(inputs);
  auto bucket = perfect_map.get_bucket();
  std::vector<int> in_buckets;
  for (auto elem : bucket) {
    cpstl::cp_log(LOG, "With Hash -> " + std::to_string(elem.first));
    cpstl::cp_log(LOG, elem.second);
    for (auto e : elem.second) {
      if (e != std::numeric_limits<int>::min()) in_buckets.push_back(e);
    }
  }
  cpstl::assert_is_true("TEST_CASE_ONE_PERFECT_HASH",
                        in_buckets.size() == inputs.size());
  std::sort(inputs.begin(), inputs.end());
  std::sort(in_buckets.begin(), in_buckets.end());
  cpstl::cp_log(LOG, inputs);
  cpstl::cp_log(LOG, in_buckets);
}

void TEST_CASE_ONE_CUCKOO_HASHING() {
  std::vector<int> inputs = {11, 25, 36, 41, 57, 66, 73, 89, 95};
  cpstl::CuckooHashing<int> cuckoo_map(inputs.size());
  for (auto elem : inputs) {
    cuckoo_map.insert(elem);
  }
  auto correct = true;
  for (auto elem : inputs) {
    auto find = cuckoo_map.at(elem);
    if (!find) {
      cpstl::cp_log(LOG, "Key is not present: " + std::to_string(elem));
      correct = false;
      break;
    }
  }
  cpstl::assert_is_true("TEST_CASE_ONE_CUCKOO_HASHING", correct);
  cpstl::cp_log(LOG, inputs);
}

int main() {
  TEST_CASE_ONE();
  TEST_CASE_ONE_PERFECT_HASH();
  TEST_CASE_ONE_CUCKOO_HASHING();
  return EXIT_SUCCESS;
}
