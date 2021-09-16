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
#ifndef BSTREE_H
#define BSTREE_H

#include <memory>

namespace cpstl {

  template <class T>
  class BSTree;

  namespace internal {

    template <class T>
    class Node {
    private:
      std::shared_ptr<Node<T>> left;
      std::shared_ptr<Node<T>> righ;
      friend cpstl::BTree<T>;
    };
  };

  template <class T>
  class BSTree {
  private:
    std::shared_ptr<internal::Node<T>> root;

  public:

    void insert(T const &value) { }

    void remove(T const &value) { }

    T get_at(std::size_t index) { }
 };

};

#endif
