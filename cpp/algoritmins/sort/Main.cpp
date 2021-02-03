/**
 * Sort algorithm's C++ implementation
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
#include <iostream>
#include <vector>

#include "Order.hpp"

using namespace std;
using namespace cpstl;

int main() {
  vector<int> inputs = {3, 4, 5, 2, 1};
  merge_sort<int>(inputs, 0, inputs.size() - 1);

  for (auto elem : inputs) cout << elem << " ";
  cout << "\n";

  assert(inputs.at(0) == 1);
  assert(inputs.at(1) == 2);
  assert(inputs.at(2) == 3);
  assert(inputs.at(3) == 4);
  assert(inputs.at(4) == 5);

  return EXIT_SUCCESS;
}
