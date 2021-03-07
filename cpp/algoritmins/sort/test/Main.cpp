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
#include <vector>

#include "../Order.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

using namespace std;

const cpstl::Log LOG(true);

void TEST_CASE_MERGE_SORT() {
  vector<int> inputs = {20, 90, 40, 1, 32};
  cpstl::merge_sort(inputs, 0, inputs.size() - 1);
  cpstl::assert_equal("TEST_CASE_MERGE_SORT", {1, 20, 32, 40, 90}, inputs);
}

void TEST_CASE_QUICK_SORT() {
  vector<int> inputs = {20, 90, 40, 1, 32};
  cpstl::quick_sort(inputs, 0, inputs.size() - 1);
  cpstl::assert_equal("TEST_CASE_QUICK_SORT", {1, 20, 32, 40, 90}, inputs);
  cpstl::cp_log(LOG, inputs);
}

void TEST_CASE_RANDOMIZED_QUICK_SORT() {
  vector<int> inputs = {20, 90, 40, 1, 32};
  cpstl::randomize_quick_sort(inputs, 0, inputs.size() - 1);
  cpstl::assert_equal("TEST_CASE_RANDOMIZED_QUICK_SORT", {1, 20, 32, 40, 90},
                      inputs);
  cpstl::cp_log(LOG, inputs);
}

int main() {
  TEST_CASE_MERGE_SORT();
  TEST_CASE_QUICK_SORT();
  TEST_CASE_RANDOMIZED_QUICK_SORT();
  return EXIT_SUCCESS;
}
