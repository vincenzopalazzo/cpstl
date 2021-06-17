/**
 * Thread safe Stack implementation C++ implementation
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

#ifndef STACK_H
#define STACK_H

#include <atomic>
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

namespace cpstl {

namespace internal {
template <class T>
class Node {
 public:
  friend class Stack;
  std::shared_ptr<T> data;
  internal::Node<T> *next;

  Node(T const &data) : data(std::make_shared<T>(data)) {}
};

class EmptyStackException : public std::runtime_error {
 public:
  EmptyStackException(const std::string &cause) throw()
      : std::runtime_error(cause){};
};
};  // namespace internal

template <class T>
class Stack {
 private:
  // With C++ 20 is possible use atomic<shared_ptr>
  // See https://en.cppreference.com/w/cpp/memory/shared_ptr/atomic2
  std::atomic<internal::Node<T> *> head;

 public:
  void push(T const &data) {
    auto node = new internal::Node<T>(data);
    node->next = head.load();
    while (!head.compare_exchange_weak(node->next, node))
      ;
  }

  std::shared_ptr<T> pop() {
    auto prev_head = head.load();
    while (prev_head && !head.compare_exchange_weak(prev_head, prev_head->next))
      ;
    return prev_head ? prev_head->data : std::shared_ptr<T>();
  }

  bool is_empty() { return head.load() == nullptr; }
};

namespace thread_safe {
template <class T>
class Stack {
 private:
  std::stack<T> data;
  mutable std::mutex g_lock;

 public:
  Stack() {}
  Stack(const Stack<T> &stack) {
    std::lock_guard<std::mutex> lock(stack.g_lock);
    data = stack.data;
  }

  Stack &operator=(const Stack &) = delete;

  void push(T val) {
    std::lock_guard<std::mutex> lock(g_lock);
    data.push(std::move(val));
  }

  std::shared_ptr<T> pop() {
    std::lock_guard<std::mutex> lock(g_lock);
    if (data.empty()) throw internal::EmptyStackException("Empty Stack");
    std::shared_ptr<T> const val(std::make_shared<T>(data.top()));
    data.pop();
    return val;
  }

  bool is_empty() {
    std::lock_guard<std::mutex> lock(g_lock);
    return data.empty();
  }
};
};  // namespace thread_safe
};  // namespace cpstl

#endif
