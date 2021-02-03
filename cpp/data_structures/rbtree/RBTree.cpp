//
// Created by vincent on 9/20/20.
//
#include "RBTree.h"

#include <iostream>

using namespace cpstl;

template <class T>
T RBTree<T>::max_value() {
  Node<T> *max = this->root;
  while (max->right) {
    max = max->right;
  }
  return max->key;
}

template <class T>
T RBTree<T>::min_value() {
  Node<T> *min = this->root;
  while (min->left) {
    min = min->left;
  }
  return min->key;
}

template <class T>
void RBTree<T>::insert_node(T value) {
  Node<T> *z = new Node<T>(value);
  Node<T> *y = NIL;
  Node<T> *x = this->root;
  while (x != NIL) {
    y = x;
    if (value < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == NIL) {
    this->root = z;
  } else if (value < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
  delete x;
  delete y;
  z->red = true;  // All new node insert inside the RB tree are red
  rb_insert_fixup(z);
}

template <class T>
void RBTree<T>::rb_insert_fixup(Node<T> *&new_node) {
  while (new_node->parent != NIL && new_node->parent->red) {
    if (new_node->parent == new_node->parent->parent->left) {
      Node<T> *gran_parent = new_node->parent->parent->right;
      if (gran_parent->red) {
        new_node->parent->red = false;
        gran_parent->red = false;
        new_node->parent->parent->red = true;
        new_node = new_node->parent->parent;
      } else {
        if (new_node->key == new_node->parent->right->key) {
          left_rotation(new_node->parent);
        } else {
          new_node->parent->red = false;
          new_node->parent->parent->red = false;
          right_rotation(new_node->parent->parent);
        }
      }
      delete gran_parent;
    } else {
      Node<T> *y = new_node->parent->parent->left;
      if (y->red) {
        new_node->parent->red = false;
        y->red = false;
        new_node->parent->parent->red = true;
        new_node = new_node->parent->parent;
      } else {
        if (new_node == new_node->parent->left) {
          left_rotation(new_node->parent);
        } else {
          new_node->parent->red = false;
          new_node->parent->parent->red = false;
          right_rotation(new_node->parent->parent);
        }
      }
      delete y;
    }
  }
  this->root->red = false;
}

template <class T>
void RBTree<T>::left_rotation(Node<T> *&value) {
  Node<T> *child = value->right;
  value->right = child->left;
  if (child->left != NIL) {
    child->left->parent = value;
  }
  child->parent = value->parent;
  if (value->parent == NIL) {
    this->root = child;
  } else if (value == value->parent->left) {
    value->parent->left = child;
  } else {
    value->parent->right = child;
  }
  child->left = value;
  value->parent = child;
}

template <class T>
void RBTree<T>::right_rotation(Node<T> *&value) {
  Node<T> *left_child = value->left;
  value->left = left_child->right;
  if (left_child->right != NIL) {
    left_child->right->parent = value;
  }
  if (value->parent == NIL) {
    left_child->parent = value->parent;
    this->root = left_child;
  } else if (value == value->parent->right) {
    value->parent->right = left_child;
  } else {
    value->parent->right = left_child;
  }
  left_child->right = value;
  value->parent = left_child;
}

template <class T>
Node<T> *RBTree<T>::search_value(T value) {
  return search_value_rb(this->root, value);
}

template <class T>
Node<T> *RBTree<T>::search_value_rb(Node<T> *&node, T value) {
  Node<T> *search = node;
  if (search->key < value) {
    search_value_rb(search->right, value);
  } else if (search->key > value) {
    search_value_rb(search->left, value);
  }
  return search;
}

template class cpstl::RBTree<int>;