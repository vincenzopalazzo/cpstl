/**
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */
#include <vector>
#include <cmath>
#include "../Search.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

using namespace std;

void TEST_CASE_ONE_BINARY_SEARCH()
{
    vector<int> inputs;
    for (int i = 1; i <= 10000; i++) {
      inputs.push_back(pow(2, i));
    }
    auto index = cpstl::Search<int, int>::binary_search(inputs, inputs[99]);
    cpstl::assert_equal("TEST_CASE_ONE_BINARY_SEARCH", inputs[index], inputs[99]);
}

void TEST_CASE_ONE_EXPONENTIAL_SEARCH()
{
  vector<int> inputs;
  for (int i = 1; i < 10000; i++) {
    inputs.push_back(pow(2, i));
  }
  auto index = cpstl::Search<int, int>::exponential_search(inputs, inputs[9999]);
  cpstl::assert_equal("TEST_CASE_ONE_EXPONENTIAL_SEARCH", inputs[index], inputs[9999]);
}

int main()
{
    TEST_CASE_ONE_BINARY_SEARCH();
    TEST_CASE_ONE_EXPONENTIAL_SEARCH();
    return EXIT_SUCCESS;
}
