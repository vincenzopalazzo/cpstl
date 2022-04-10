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
#include <string>
#include <vector>

#include "../Order.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

const cpstl::Log LOG(true);

void TEST_CASE_MERGE_SORT() {
  std::vector<int> inputs = {20, 90, 40, 1, 32};
  auto order = cpstl::Order<int>();
  order.merge_sort(inputs, 0, inputs.size() - 1);
  cpstl::assert_equal("TEST_CASE_MERGE_SORT", {1, 20, 32, 40, 90}, inputs);
}

void TEST_CASE_QUICK_SORT() {
  std::vector<int> inputs = {20, 90, 40, 1, 32};
  auto order = cpstl::Order<int>();
  order.quick_sort(inputs, 0, inputs.size() - 1);
  cpstl::assert_equal("TEST_CASE_QUICK_SORT", {1, 20, 32, 40, 90}, inputs);
  cpstl::cp_log(LOG, inputs);
}

void TEST_CASE_RANDOMIZED_QUICK_SORT() {
  std::vector<int> inputs = {20, 90, 40, 1, 32};
  auto order = cpstl::Order<int>();
  order.randomize_quick_sort(inputs, 0, inputs.size() - 1);
  cpstl::assert_equal("TEST_CASE_RANDOMIZED_QUICK_SORT", {1, 20, 32, 40, 90},
                      inputs);
  cpstl::cp_log(LOG, inputs);
}

void TEST_CASE_COUNTING_SORT() {
  std::vector<int> inputs = {20, 90, 40, 1, 32};
  auto order = cpstl::Order<int>();
  order.counting_sort(inputs, 1, 90);
  cpstl::assert_equal("TEST_CASE_COUNTING_SORT", {1, 20, 32, 40, 90}, inputs);
  cpstl::cp_log(LOG, inputs);
}

void TEST_CASE_ODD_EVEN_SORT() {
  std::vector<int> inputs = {20, 90, 40, 1, 32};
  auto order = cpstl::Order<int>();
  order.odd_even_sort(inputs, 0, inputs.size());

  cpstl::assert_equal("TEST_CASE_ODD_EVEN_SORT", {1, 20, 32, 40, 90}, inputs);
  cpstl::cp_log(LOG, inputs);
}

int main() {
  TEST_CASE_MERGE_SORT();
  TEST_CASE_QUICK_SORT();
  TEST_CASE_RANDOMIZED_QUICK_SORT();
  TEST_CASE_COUNTING_SORT();
  TEST_CASE_ODD_EVEN_SORT();
  return EXIT_SUCCESS;
}
