/**
 * Linked List C++ implementation
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
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <vector>
#include <memory>
#include <cassert>

namespace cpstl {

  /**
   * Implementation of the class Node, that it is used to
   * managed the pointer inside the data-stucture.
   */
  template<class T>
  class LinkedList;

  namespace internal {
    /**
     * Implementation of the class Node, that it is used to
     * managed the pointer inside the data-stucture.
     */
    template <class T>
    class Node {
    private:
      T value;
      std::shared_ptr<Node<T>> next = nullptr;
      std::shared_ptr<Node<T>> prev = nullptr;
      friend cpstl::LinkedList<T>;

    public:
      Node(T const& value): value(value) {}

      Node(T const& value,
                     std::shared_ptr<Node<T>> const &next,
                     std::shared_ptr<Node<T>> const &prev):
        value(value), next(next), prev(prev) {}
    };
  };

  /**
   * LinkedList implementation, it offer an implementation of the
   * LinkedList double linked.
   */
  template <class T>
  class LinkedList {
  private:
    std::size_t size_list;
    std::shared_ptr<internal::Node<T>> head = nullptr;
    std::shared_ptr<internal::Node<T>> tail = nullptr;

  public:

    constexpr LinkedList(): size_list(0) {}

    /**
     * Adding the value to the end of the list.
     * Cost of the operation O(1).
     */
    void add(T const &value) {
      auto node =
        std::make_shared<internal::Node<T>>(value);
      if (!head) {
        this->head = node;
        this->tail = node;
        return;
      }
      node->prev = this->tail;
      this->tail->next = node;
      this->tail = node;
    }

    /**
     * Remove the first instance find inside list,
     * in according with the insert order.
     */
    void remove(T const &value) { }

    /**
     * Remove the element at the index,
     */
    void remove_at(std::size_t index) { }

    /**
     * Swap two element in the list
     */
    void swap(std::size_t x, std::size_t y) { }

    std::vector<T> to_vector() {
      if (!head)
        return {};

      // This time we use the for to iterate over the list
      std::vector<T> result;
      result.reserve(size_list);
      bool has_next = this->head != nullptr;
      auto node = *head;
      while (has_next) {
        result.push_back(node.value);
        has_next = node.next != nullptr;
        if (has_next)
          node = *node.next;
      }
      return result;
    }

    std::string to_string(std::string seperator = ", ") {
      if (!this->head)
        return "";
      auto start = *this->head;
      bool has_next = true;
      std::string concatenation = "";
      while (has_next) {
        std::string result = std::to_string(start.value);
        has_next = start.next != nullptr;
        if (has_next) {
          start = *start.next;
          result += seperator;
        }
        concatenation += result;
      }
      return concatenation;
    }

    /**
     * Adding a value in position index of the list
     * this operation takes just O(N) there here in the
     * worst case the N is the size of the list.
     */
    void add_at(T const &value, std::size_t index) {
      assert(index < size_list);
    }

    internal::Node<T> back() {
      return this->tail;
    }

    internal::Node<T>* begin() {
      return this->head;
    }
  };
};

#endif
