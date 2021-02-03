/**
 * Search algorithm's C++ implementation
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
#include <cmath>
#include <iostream>
#include <vector>

#include "Search.hpp"

int main() {
  std::vector<int> inputs;

  for (int i = 0; i < 30; i++) inputs.push_back(std::pow(2, i));

  std::cout << "Input ";
  for (auto elem : inputs) std::cout << elem << " ";
  std::cout << std::endl;

  std::cout << "search " << inputs.at(2) << std::endl;
  int index = cpstl::binary_search(inputs, inputs.at(2), 0, inputs.size() - 1);
  std::cout << "Index found is: " << index << std::endl;
  if (index != -1) std::cout << "Element is: " << inputs.at(index) << std::endl;

  std::cout << "search 100" << std::endl;
  index = cpstl::binary_search(inputs, inputs.at(inputs.size() - 2), 0,
                               inputs.size() - 1);
  std::cout << "Index found is: " << index << std::endl;
  if (index != -1) std::cout << "Element is: " << inputs.at(index) << std::endl;

  std::cout << "-------- Exponential Searching -------\n";
  std::cout << "search " << inputs.at(2) << std::endl;
  index = cpstl::exponential_search(inputs, inputs.at(2));
  std::cout << "Index found is: " << index << std::endl;
  if (index != -1) std::cout << "Element is: " << inputs.at(index) << std::endl;
  std::cout << "search " << inputs.at(inputs.size() - 2) << std::endl;
  index = cpstl::exponential_search(inputs, inputs.at(inputs.size() - 2));
  std::cout << "Index found is: " << index << std::endl;
  if (index != -1) std::cout << "Element is: " << inputs.at(index) << std::endl;
}
