//
// Created by vincent on 9/20/20.
//

#include <iostream>
#include <memory>

#include "RBTree.h"

using namespace cpstl;

template <class T>
void print_level_tree(const cpstl::Node<T> *root, std::string elem);

int main() {
  RBTree<int> *tree = new RBTree<int>(10);
  std::cout << "-------- Insert -----------" << std::endl;
  tree->insert_node(12);
  tree->insert_node(13);
  // tree->insert_node(11);
  print_level_tree<int>(tree->get_root(), "Root");

  /*std::cout << "-------- delete -----------" << std::endl;
  btree::delete_node(tree.get(), 2);
  btree::delete_node(tree.get(), 10);
  print_level_tree(tree.get());*/

  return EXIT_SUCCESS;
}

template <class T>
void print_level_tree(const cpstl::Node<T> *root, std::string elem) {
  if (root == NIL) return;

  std::cout << elem << " " << root->key << std::endl;

  if (root->left) print_level_tree(root->left, "left");

  if (root->right) print_level_tree(root->right, "right");
}