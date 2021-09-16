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

#include <memory>

namespace cpstl {

  template <class T>
  class BTree;

  namespace internal {

    template <class T>
    class Node {
    private:
      T value;
      std::shared_ptr<Node<T>> left;
      std::shared_ptr<Node<T>> right;
      friend cpstl::BTree<T>;

    public:
      Node(T const &value): value(value) {}
    };
  };

  template <class T>
  class BTree {
  private:
    std::shared_ptr<internal::Node<T>> root;

    void insert_helper(std::shared_ptr<internal::Node<T>> node, T const &value) {
      if (!node) {
        node = std::make_shared<internal::Node<T>>(value);
        return;
      }

      if (value < node->value) {
        //Move to the left
        insert_helper(node->left, value);
        return;
      }
      // move to the right
      insert_helper(node->right, value);
    }

  public:

    bool is_empty() {
      return root == nullptr;
    }

    bool is_root_tree() {
      if (!root)
        return false;
      return root->left == nullptr && root->righ == nullptr;
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
    }

    /**
     * Get element at position index
     */
    T get_at(std::size_t index) { }
 };

};

#endif
