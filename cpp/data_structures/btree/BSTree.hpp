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
#include <memory>

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
      Node(T const &value): value(value) {}
      Node(T const &value, std::shared_ptr<internal::Node<T>> node):
        value(value), parent(node) {}
    };
  };

  template <class T>
  class BTree {
  private:
    std::shared_ptr<internal::Node<T>> root;

    bool contains_helper(std::shared_ptr<internal::Node<T>> node, T const &value) {
      if (!node)
        return false;
      if (node->value == value)
        return true;

      if (node->value > value)
        return contains_helper(node->left, value);
      return contains_helper(node->right, value);
    }

    void insert_helper(std::shared_ptr<internal::Node<T>> node, T const &value) {
      if (value < node->value) {
        //Move to the left
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

    std::shared_ptr<internal::Node<T>> get_max_to_left(std::shared_ptr<internal::Node<T>> node) {
      if (!node->right)
        return node;
      return get_max_to_left(node->right);
    }

    std::shared_ptr<internal::Node<T>> get_min_to_right(std::shared_ptr<internal::Node<T>> node) {
      assert(node);
      if (!node->left)
        return node;
      return get_min_to_right(node->left);
    }

    void remove_helper(std::shared_ptr<internal::Node<T>> node, T const &value) {
      assert(node);

      if (node->value == value) {
        if (node->left) {
          auto max_to_left = get_max_to_left(node->left);
          node->left = max_to_left->left;
          node->right = max_to_left->right;
          node->value = max_to_left->value;
          max_to_left.reset();
          // TODO: the parent still point to the node
        } else if (node->right){
          auto min_to_right = get_min_to_right(node->right);
          // take the minimum to the right
          node->left = min_to_right->left;
          node->right = min_to_right->right;
          node->value = min_to_right->value;
          min_to_right.reset();
          // TODO: the parent still point to the node
        } else {
          // it is a leaft
          node = nullptr;
        }
        return;
      }

      if (node->value > value)
        remove_helper(node->left, value);
      else
        remove_helper(node->right, value);
    }

  public:

    bool is_empty() {
      return root == nullptr;
    }

    bool is_root_tree() {
      if (!root)
        return false;
      return root->left == nullptr && root->right == nullptr;
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
      if (is_root_tree())
        return;
      remove_helper(root, value);
    }

    bool contains(T const &value) {
      return contains_helper(this->root, value);
    }

    /**
     * Get element at position index
     */
    T get_at(std::size_t index) { }
 };

};

#endif
