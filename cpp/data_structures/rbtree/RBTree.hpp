/**
 * Red and Black Tree data structure C++ implementation
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
#include <iostream>
#include <memory>
#include <vector>

namespace cpstl {

template <class T>
struct Node {
  Node<T> *parent = nullptr;
  Node<T> *left = nullptr;
  Node<T> *right = nullptr;
  bool red = false;
  T key;

  Node(T value) { this->key = value; }
  Node(Node<T> *parent, bool red, T key) : parent(parent), red(red), key(key) {}
};

template <class T>
class RBTree {
 private:
  enum class Side { LEFT, RIGHT };

  Node<T> *root = nullptr;
  std::size_t _size = 0;

  Node<T> *insert_procedure(Node<T> *parent, T value) {
    if (parent->key > value) {
      if (!parent->left) {
        parent->left = new Node<T>(parent, true, value);
        return parent->left;
      } else {
        return insert_procedure(parent->left, value);
      }
    } else {
      if (!parent->right) {
        parent->right = new Node<T>(parent, true, value);
        return parent->right;
      } else {
        return insert_procedure(parent->right, value);
      }
    }
  }

  void fixup_procedure(Node<T> *node) {
    RBTree::Side parent_side, child_side;
    auto parent = node->parent;
    Node<T> *uncle;
    Node<T> *gran_pa;

    if (node->red && !parent) {
      node->red = false;
      return;
    }

    if (parent) gran_pa = parent->parent;

    if (parent && gran_pa && parent->red) {
      parent_side = (gran_pa->left == parent) ? Side::LEFT : Side::RIGHT;
      child_side = (parent->left == node) ? Side::LEFT : Side::RIGHT;
      uncle = (parent_side == Side::LEFT) ? gran_pa->right : gran_pa->left;

      if (!uncle || !uncle->red) {
        if (parent_side == Side::LEFT && child_side == Side::LEFT) {
          ll_rotation(parent, gran_pa);
        } else if (parent_side == Side::LEFT && child_side == Side::RIGHT) {
          lr_rotation(node);
        } else if (parent_side == Side::RIGHT && child_side == Side::LEFT) {
          rl_rotation(node);
        } else {
          rr_rotation(parent, gran_pa);
        }
      } else {
        parent->red = false;
        uncle->red = false;
        gran_pa->red = true;
        fixup_procedure(gran_pa);
      }
    }
  }

  void ll_rotation(Node<T> *parent, Node<T> *gran_pa) {
    auto fom_gran_pa = gran_pa;
    right_rotation(parent);
    parent->red = false;
    fom_gran_pa->red = true;
  }

  void rr_rotation(Node<T> *parent, Node<T> *gran_pa) {
    auto fom_gran_pa = gran_pa;
    left_rotation(parent);
    parent->red = false;
    fom_gran_pa->red = true;
  }

  void lr_rotation(Node<T> *node) {
    left_rotation(node);
    ll_rotation(node, node->parent);
  }

  void rl_rotation(Node<T> *parent) {
    right_rotation(parent);
    rr_rotation(parent, parent->parent);
  }

  void left_rotation(Node<T> *node) {
    auto node_parent = node->parent;
    node_parent->right = node->left;

    if (node->left) node->left->parent = node_parent;

    node->parent = node_parent->parent;

    if (!node_parent->parent) {
      this->root = node;
    } else if (node_parent == node_parent->parent->left) {
      node_parent->parent->left = node;
    } else {
      node_parent->parent->right = node;
    }

    node->left = node_parent;
    node_parent->parent = node;
  }

  void right_rotation(Node<T> *node) {
    auto node_parent = node->parent;
    node_parent->left = node->right;

    if (node->right) {
      node->right->parent = node_parent;
    }
    node->parent = node_parent->parent;

    if (!node_parent->parent)
      this->root = node;
    else if (node_parent == node_parent->parent->left)
      node_parent->parent->left = node;
    else
      node_parent->parent->right = node;

    node->right = node_parent;
    node_parent->parent = node;
  }

  void visit_in_order_procedure(Node<T> *root_node, std::vector<T> &ordered) {
    if (root_node) {
      visit_in_order_procedure(root_node->left, ordered);
      ordered.push_back(root_node->key);
      visit_in_order_procedure(root_node->right, ordered);
    }
  }

  Node<T> *find_procedure(Node<T> *node, T value) {
    if (!node || node->key == value) return node;
    if (node->key > value) {
      return find_procedure(node->left, value);
    } else {
      return find_procedure(node->right, value);
    }
  }

  Node<T> *minimum(Node<T> *node) {
    auto visit_node = node;
    while (visit_node->left) {
      visit_node = visit_node->left;
    }
    return visit_node;
  }

  Node<T> *successor(Node<T> *node) {
    if (node->right) {
      return minimum(node->right);
    }
    auto x = node;
    auto y = node->parent;
    while (y && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

 public:
  RBTree() {}
  virtual ~RBTree() { delete root; }
  void insert(T value) {
    if (!root) {
      this->root = new Node<T>(value);
      _size++;
      return;
    }
    auto new_node = insert_procedure(root, value);
    fixup_procedure(new_node);
    _size++;
  }

  std::size_t size() { return _size; }

  T max() {
    auto node = root;
    while (node->right) {
      node = node->right;
    }
    return node->key;
  }

  T min() {
    auto node = minimum(this->root);
    return node->key;
  }

  std::vector<T> visit_in_order() {
    std::vector<T> ordered;
    ordered.reserve(_size);
    visit_in_order_procedure(root, ordered);
    return ordered;
  }
};
};  // namespace cpstl
