//
// Created by vincent on 9/20/20.
//
#include "BTree.h"

using namespace cpstl;

template <class T>
BTree<T>::BTree(Node<T> *&root) {
  this->root = root;
}
template <class T>
BTree<T>::BTree() {
  this->root = nullptr;
}

template <class T>
bool cpstl::BTree<T>::insert_node(T value) {
  this->root = insert_recursive(this->root, value);
  return true;
}

template <class T>
Node<T> *BTree<T>::insert_recursive(Node<T> *&node, T value) {
  if (!node) {
    node = new Node<T>(value);
  } else if (node->value > value) {
    node->left = insert_recursive(node->left, value);
  } else {
    node->right = insert_recursive(node->right, value);
  }
  return node;
}

template <class T>
void BTree<T>::transplan(Node<T> *&victim, Node<T> *&survived) {
  if (!victim->parent) {
    this->root = survived;
  } else if (victim == victim->parent->left) {
    victim->parent->left = survived;
  } else {
    victim->parent->right = survived;
  }
  if (survived) survived->parent = victim->parent;
}

template <class T>
bool BTree<T>::delete_node(T value) {
  auto victim = search_node(value);
  if (!victim) return false;
  if (!victim->right) {
    transplan(victim, victim->left);
  } else {
    auto y = tree_minimum(victim->right);
    if (y->parent != victim) {
      transplan(y, y->right);
      y->right = victim->right;
      y->right->parent = y;
    } else {
      transplan(victim, y);
      y->left = victim->left;
      y->left->parent = y;
    }
  }
  return true;
}

template <class T>
Node<T> *BTree<T>::get_root() {
  return this->root;
}

template <class T>
Node<T> *BTree<T>::tree_minimum(Node<T> *&node) {
  if (node->left) tree_minimum(node->left);
  return node;
}

template <class T>
Node<T> *BTree<T>::search_node(T value) {
  return get_node_recursive(this->root, value);
}

template <class T>
Node<T> *BTree<T>::get_node_recursive(Node<T> *&root, T key) {
  if (root == nullptr) return nullptr;
  if (root->value == key) return root;
  if (root->value > key) {
    return get_node_recursive(root->left, key);
  }
  return get_node_recursive(root->right, key);
}

template <class T>
T BTree<T>::min() {
  auto selector = this->root;
  while (selector->left) {
    selector = selector->left;
  }
  return selector->value;
}

template class cpstl::Node<int>;

template class cpstl::BTree<int>;
