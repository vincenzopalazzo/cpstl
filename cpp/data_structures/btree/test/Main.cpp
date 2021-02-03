//
// Created by vincent on 9/14/20.
//
#include <cstdlib>
#include <fstream>
#include <vector>

#include "../BTree.h"
#include "TestTool.h"
#include "Utils.h"

using namespace std;
using namespace cpstl;

void TEST_CASE_ONE() {
  cpstl::BTree<int> tree;
  tree.insert_node(50);
  tree.insert_node(102);
  tree.insert_node(49);

  std::cout << "-------- Insert -----------" << std::endl;
  cpstl::print_level_tree(tree.get_root(), "Root");

  std::cout << "-------- delete -----------" << std::endl;
  tree.delete_node(49);
  print_level_tree(tree.get_root(), "Root");
  // assert_equal("TEST_CASE_ONE", 2, maximum_house);
}

void TEST_CASE_TWO() {
  cpstl::BTree<int> tree;
  tree.insert_node(4);
  tree.insert_node(2);
  tree.insert_node(5);
  tree.insert_node(1);
  tree.insert_node(6);
  tree.insert_node(3);

  std::cout << "-------- Insert -----------" << std::endl;
  cpstl::print_level_tree(tree.get_root(), "Root");

  std::cout << "-------- delete -----------" << std::endl;
  tree.delete_node(3);
  cpstl::print_level_tree(tree.get_root(), "Root");
  // assert_equal("TEST_CASE_ONE", 2, maximum_house);
}

int main() {
  TEST_CASE_ONE();
  TEST_CASE_TWO();

  return EXIT_SUCCESS;
}