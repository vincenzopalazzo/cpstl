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

#include "../BSTree.hpp"
#include "TestTool.hpp"
#include "Utils.hpp"

using namespace std;

static void TEST_CREATE_BTREE() {
  auto bstree = cpstl::BTree<int>();

  bstree.insert(1);
  bstree.insert(2);
  bstree.insert(-1);

  cpstl::assert_is_true("TEST_CREATE_BSTREE_CONTAINS_1", bstree.contains(1));
  cpstl::assert_is_true("TEST_CREATE_BSTREE_CONTAINS_2", bstree.contains(2));
  cpstl::assert_is_true("TEST_CREATE_BSTREE_CONTAINS_-1", bstree.contains(-1));
  cpstl::assert_equal("TEST_CREATE_BSTREE_CONTAINS_ROOT", bstree.get_root(), 1);

  bstree.remove(-1);
  cpstl::assert_is_true("TEST_CREATE_BSTREE_REMOVE_-1", !bstree.contains(-1));
  cpstl::assert_is_true("TEST_CREATE_BSTREE_CONTAINS_1", bstree.contains(1));
  cpstl::assert_is_true("TEST_CREATE_BSTREE_CONTAINS_2", bstree.contains(2));

  bstree.remove(2);
  cpstl::assert_is_true("TEST_CREATE_BSTREE_REMOVE_-1", !bstree.contains(-1));
  cpstl::assert_is_true("TEST_CREATE_BSTREE_CONTAINS_1", bstree.contains(1));
  cpstl::assert_is_true("TEST_CREATE_BSTREE_REMOVE_2", !bstree.contains(2));

  cpstl::assert_is_true("TEST_CREATE_BSTREE_ISROOTED", bstree.is_root_tree());
  cpstl::assert_is_true("TEST_CREATE_BSTREE_NOT_EMPTY", !bstree.is_empty());

  bstree.clear();
  cpstl::assert_is_true("TEST_CREATE_BSTREE_EMPTY", bstree.is_empty());

}

static void TEST_REMOVE_ROOT_BTREE() {
  auto bstree = cpstl::BTree<int>();

  bstree.insert(1);
  bstree.insert(2);
  bstree.insert(-1);

  cpstl::assert_is_true("TEST_CREATE_BSTREE_CONTAINS_1", bstree.contains(1));
  cpstl::assert_is_true("TEST_CREATE_BSTREE_CONTAINS_2", bstree.contains(2));
  cpstl::assert_is_true("TEST_CREATE_BSTREE_CONTAINS_-1", bstree.contains(-1));
  cpstl::assert_equal("TEST_CREATE_BSTREE_CONTAINS_ROOT", bstree.get_root(), 1);

  bstree.remove(1);
  cpstl::assert_equal("TEST_CREATE_BSTREE_CONTAINS_ROOT", bstree.get_root(), -1);
}


int main() {
  TEST_CREATE_BTREE();
  TEST_REMOVE_ROOT_BTREE();
  return EXIT_SUCCESS;
}
