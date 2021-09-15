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

#include "../LinkedList.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

using namespace std;


static void TEST_ONE_LINKED_LIST_ADD() {
  auto list = cpstl::LinkedList<int>();
  list.add(12);

  cpstl::assert_equal("TEST_ONE_LINKED_LIST_ADD", (std::string)"12", list.to_string());

  list.add(150);

  cpstl::assert_equal("TEST_ONE_LINKED_LIST_ADD", (std::string)"12, 150", list.to_string());

  auto vect = list.to_vector();
  cpstl::assert_equal("TEST_ONE_LINKED_LIST_ADD", {12, 150}, vect);
}


int main() {
  TEST_ONE_LINKED_LIST_ADD();
  return EXIT_SUCCESS;
}
