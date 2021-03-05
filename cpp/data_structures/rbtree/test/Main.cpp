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

#include "../RBTree.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

using namespace std;
using namespace cpstl;

void TEST_CASE_ONE_RBTREE() {
  auto balanced_tree = RBTree<int>();
  balanced_tree.insert(2);
  balanced_tree.insert(1);
  balanced_tree.insert(3);
  balanced_tree.insert(4);
  balanced_tree.insert(32);
  balanced_tree.insert(24);
  balanced_tree.insert(35);
  balanced_tree.insert(22);
  assert_equal("TEST_CASE_ONE_RBTREE_SIZE", 8, (int)balanced_tree.size());
  assert_equal("TEST_CASE_ONE_RBTREE_MAX", 35, balanced_tree.max());
  assert_equal("TEST_CASE_ONE_RBTREE_MIN", 1, balanced_tree.min());
  auto order_elements = balanced_tree.visit_in_order();
  assert_equal("TEST_CASE_ONE_RBTREE", {1, 2, 3, 4, 22, 24, 32, 35},
               order_elements);
}

void TEST_CASE_TWO_RBTREE() {
  auto balanced_tree = RBTree<int>();
  balanced_tree.insert(345);
  balanced_tree.insert(3);
  balanced_tree.insert(2);
  balanced_tree.insert(4343);
  balanced_tree.insert(44);
  balanced_tree.insert(41);
  assert_equal("TEST_CASE_TWO_RBTREE_SIZE", 6, (int)balanced_tree.size());
  assert_equal("TEST_CASE_TWO_RBTREE_MAX", 4343, balanced_tree.max());
  assert_equal("TEST_CASE_TWO_RBTREE_MIN", 2, balanced_tree.min());
  auto order_elements = balanced_tree.visit_in_order();
  assert_equal("TEST_CASE_TWO_RBTREE", {2, 3, 41, 44, 345, 4343},
               order_elements);
}

void TEST_CASE_TWO_RBTREE_DELETE() {
  auto balanced_tree = RBTree<int>();
  balanced_tree.insert(345);
  balanced_tree.insert(3);
  balanced_tree.insert(2);
  balanced_tree.insert(4343);
  balanced_tree.insert(44);
  balanced_tree.insert(41);
  assert_equal("TEST_CASE_TWO_RBTREE_SIZE_DELETE", 6,
               (int)balanced_tree.size());
  assert_equal("TEST_CASE_TWO_RBTREE_MAX_DELETE", 4343, balanced_tree.max());
  assert_equal("TEST_CASE_TWO_RBTREE_MIN_DELETE", 2, balanced_tree.min());
  auto order_elements = balanced_tree.visit_in_order();
  assert_equal("TEST_CASE_TWO_RBTREE_DELETE", {2, 3, 41, 44, 345, 4343},
               order_elements);
}

int main() {
  TEST_CASE_ONE_RBTREE();
  TEST_CASE_TWO_RBTREE();
  TEST_CASE_TWO_RBTREE_DELETE();
  return EXIT_SUCCESS;
}
