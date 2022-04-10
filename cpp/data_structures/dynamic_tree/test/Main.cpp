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
#include <fstream>
#include <vector>

#include "../DynamicTree.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

using namespace std;
using namespace cpstl;

void TEST_CASE_ONE() {
  auto tree = cpstl::DynamicTree<int>("root", 1);
  auto result = tree.insert("insert", 12);
  assert_is_true("TEST_CASE_ONE", result);
}

int main() {
  TEST_CASE_ONE();
  return EXIT_SUCCESS;
}
