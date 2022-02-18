/**
 * Binary Tree implementation in C++ 14
 * Copyright (C) 2021 Vincenzo Palazzo vincenzopalazzodev@gmail.com
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
#ifndef BTREE_H
#define BTREE_H

#include <cassert>
#include <climits>
#include <memory>
#include <vector>

namespace cpstl {

template <class T>
class BTree;

namespace internal {

template <class T>
class Node {
 private:
  T value;
  std::shared_ptr<Node<T>> parent = nullptr;
  std::shared_ptr<Node<T>> left = nullptr;
  std::shared_ptr<Node<T>> right = nullptr;
  friend cpstl::BTree<T>;

 public:
  Node(T const &value) : value(value) {}
  Node(T const &value, std::shared_ptr<internal::Node<T>> node)
      : value(value), parent(node) {}
};
};  // namespace internal

template <class T>
class BTree {
 private:
  std::shared_ptr<internal::Node<T>> root;

  bool contains_helper(std::shared_ptr<internal::Node<T>> node,
                       T const &value) {
    if (!node) return false;
    if (node->value == value) return true;

    if (node->value > value) return contains_helper(node->left, value);
    return contains_helper(node->right, value);
  }

  void insert_helper(std::shared_ptr<internal::Node<T>> node, T const &value) {
    if (value < node->value) {
      // Move to the left
      if (node->left)
        insert_helper(node->left, value);
      else
        node->left = std::make_shared<internal::Node<T>>(value, node);
      return;
    }
    // move to the right
    if (node->right)
      insert_helper(node->right, value);
    else
      node->right = std::make_shared<internal::Node<T>>(value, node);
  }

  std::shared_ptr<internal::Node<T>> get_max_to_left(
      std::shared_ptr<internal::Node<T>> node) {
    if (!node->right) return node;
    return get_max_to_left(node->right);
  }

  std::shared_ptr<internal::Node<T>> get_min_to_right(
      std::shared_ptr<internal::Node<T>> node) {
    assert(node);
    if (!node->left) return node;
    return get_min_to_right(node->left);
  }

  void mapping_node(std::shared_ptr<internal::Node<T>> from,
                    std::shared_ptr<internal::Node<T>> to, bool left) {
    to->left = from->left;
    to->right = from->right;
    to->value = from->value;
    // It is correct?
    to->parent = from->parent;
    // TODO: Add the logic to handler also the parent option
  }

  void remove_helper(std::shared_ptr<internal::Node<T>> node, bool left,
                     T const &value) {
    assert(node);

    if (node->value == value) {
      /// TODO: there is recursion bug when we are going to
      // remove and print it.
      // The bug was founding during the porting into vlang
      // https://github.com/vlang/v/pull/13453/files
      if (node->left) {
        auto max_to_left = get_max_to_left(node->left);
        mapping_node(max_to_left, node, true);
        auto parent = max_to_left->parent;
        parent->right = node;
        max_to_left.reset();
      } else if (node->right) {
        // take the minimum to the right
        auto min_to_right = get_min_to_right(node->right);
        mapping_node(min_to_right, node, false);
        auto parent = min_to_right->parent;
        parent->left = node;
        min_to_right.reset();
      } else {
        auto parent = node->parent;
        if (left)
          parent->left = nullptr;
        else
          parent->right = nullptr;
        // it is a leaft
        node.reset();
      }
      return;
    }

    if (node->value > value)
      remove_helper(node->left, true, value);
    else
      remove_helper(node->right, false, value);
  }

  /**
   * This helper it is a little bit tricky if the user don't think all the user
   * keys like me when I wrote the first version of this code.
   * we need to pass max and min, because we can have a subtree valid, but all
   * the tree it is invalid because we have a wrong sequence of nodes.
   */
  bool is_valid_bst_helper(std::shared_ptr<internal::Node<T>> node, T min,
                           T max) {
    if (node->value < min || node->value >= max) return true;
    if (node->left && !is_valid_bst_helper(node->left, min, node->value))
      return false;

    if (node->right && !is_valid_bst_helper(node->right, node->value, max))
      return false;
    return true;
  }

  void traverse_in_order_helper(std::shared_ptr<internal::Node<T>> node,
                                std::vector<T> &result) {
    if (!node) return;

    traverse_in_order_helper(node->left, result);
    result.push_back(node->value);
    traverse_in_order_helper(node->right, result);
  }

  void traverse_post_order_helper(std::shared_ptr<internal::Node<T>> node,
                                  std::vector<T> &result) {
    if (!node) return;

    traverse_post_order_helper(node->left, result);
    traverse_post_order_helper(node->right, result);
    result.push_back(node->value);
  }

  void traverse_pre_order_helper(std::shared_ptr<internal::Node<T>> node,
                                 std::vector<T> &result) {
    if (!node) return;

    result.push_back(node->value);
    traverse_pre_order_helper(node->left, result);
    traverse_pre_order_helper(node->right, result);
  }

 public:
  bool is_empty() { return root == nullptr; }

  bool is_root_tree() {
    if (!root) return false;
    return root->left == nullptr && root->right == nullptr;
  }

  T get_root() { return root->value; }

  void clear() {
    // We assume that it is without child
    // the tree has only the root.
    assert(is_root_tree());
    root.reset();
    root = nullptr;
  }

  bool is_valid_bst() {
    // A empty tree it is valid
    if (is_empty()) return true;
    return is_valid_bst_helper(root, INT_MIN, INT_MAX);
  }

  /**
   * insert value in the bst.
   */
  void insert(T const &value) {
    if (is_empty()) {
      root = std::make_shared<internal::Node<T>>(value);
      return;
    }
    insert_helper(root, value);
  }

  /**
   * Remove value in the bst.
   */
  void remove(T const &value) {
    // It is no possible destroy a bst
    if (is_root_tree()) return;
    remove_helper(root, true, value);
  }

  std::vector<T> traverse_in_order() {
    std::vector<T> result;
    traverse_in_order_helper(root, result);
    return result;
  }

  std::vector<T> traverse_post_order() {
    std::vector<T> result;
    traverse_post_order_helper(root, result);
    return result;
  }

  std::vector<T> traverse_pre_order() {
    std::vector<T> result;
    traverse_pre_order_helper(root, result);
    return result;
  }

  bool contains(T const &value) { return contains_helper(this->root, value); }

  /**
   * Get element at position index
   */
  T get_at(std::size_t index) {}
};

};  // namespace cpstl

#endif
