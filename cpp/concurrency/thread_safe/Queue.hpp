/**
 * Thread safe Queue implementation C++ implementation
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

#ifndef QUEUE_H
#define QUEUE_H

#include <atomic>
#include <condition_variable>
#include <exception>
#include <memory>
#include <mutex>
#include <queue>

namespace cpstl {

namespace internal {}

namespace thread_safe {
template <class T>
class Queue {
 private:
  mutable std::mutex g_lock;
  std::queue<std::shared_ptr<T>> data;
  std::condition_variable cond;

 public:
  Queue() {}

  void wait_and_pop(T &value) {
    std::unique_lock<std::mutex> lock(g_lock);
    cond.wait(lock, [&] { return !data.empty(); });
    value = std::move(*data.front());
    data.pop();
  }

  bool try_pop(T &value) {
    std::lock_guard<std::mutex> lock(g_lock);
    if (data.empty) return false;
    value = std::move(*data.front());
    data.pop();
    return true;
  }

  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lock(g_lock);
    cond.wait(lock, [&] { return !data.empty(); });
    auto elem = data.front();
    data.pop();
    return elem;
  }

  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> lock(g_lock);
    if (data.empty()) return std::shared_ptr<T>();
    auto value = data.front();
    data.pop();
    return value;
  }

  void push(T const &value) {
    // perform the allocation out of the lock.
    auto alloc = std::make_shared<T>(std::move(value));
    std::lock_guard<std::mutex> lock(g_lock);
    data.push(alloc);
    cond.notify_one();
  }

  bool is_empty() {
    std::lock_guard<std::mutex> lock(g_lock);
    return data.empty();
  }
};
};  // namespace thread_safe
};  // namespace cpstl

#endif
