/**
 * Thread safe Hash Map C++ 17 implementation
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

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <exception>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <shared_mutex>

namespace cpstl {

namespace internal {
template <typename Key, typename Value>
class Bucket {
 private:
  std::list<std::pair<Key, Value>> data;
  mutable std::shared_mutex mutex;

  typename std::list<std::pair<Key, Value>>::iterator find_with_key(
      Key const &key) {
    return std::find_if(
        data.begin(), data.end(),
        [&](std::pair<Key, Value> elem) { return elem.first == key; });
  }

 public:
  Value get_def(Key const &key, Value const &def_value) {
    std::shared_lock lock(mutex);
    auto iter = find_with_key(key);
    if (iter == data.end()) return def_value;
    return iter->second;
  }

  void add(Key const &key, Value const &value) {
    std::unique_lock lock(mutex);
    auto iter = find_with_key(key);
    if (iter == data.end())
      data.emplace_back(key, value);
    else
      iter->second = value;
  }

  void remove(Key const &key) {
    std::unique_lock lock(mutex);
    auto iter = find_with_key(key);
    if (iter != data.end()) data.erase(iter);
  }
};
};  // namespace internal

namespace thread_safe {
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashMap {
 private:
  std::vector<std::unique_ptr<cpstl::internal::Bucket<Key, Value>>> buckets;
  Hash hash_function;

  cpstl::internal::Bucket<Key, Value> &get_bucket(Key const &key) const {
    auto const index = hash_function(key) % buckets.size();
    return *buckets[index];
  }

 public:
  HashMap(std::size_t buckets_size = 19, Hash const &hash_function = Hash())
      : buckets(buckets_size), hash_function(hash_function) {
    for (std::size_t i = 0; i < buckets_size; i++)
      buckets[i].reset(new cpstl::internal::Bucket<Key, Value>());
  }

  HashMap(HashMap const &other) = delete;
  HashMap &operator=(HashMap const &other) = delete;

  Value get_def(Key const &key, Value const &def_value) {
    return get_bucket(key).get_def(key, def_value);
  }

  void add(Key const &key, Value const &value) {
    get_bucket(key).add(key, value);
  }

  void remove(Key const &key) { get_bucket(key).remove(key); }

  std::map<Key, Value> to_map() const {
    std::vector<std::unique_lock<std::shared_mutex>> locks;
    for (std::size_t i = 0; i < buckets.size(); i++)
      locks.push_back(std::unique_lock<std::shared_mutex>(buckets[i].mutex));
    std::map<Key, Value> map;
    for (std::size_t i = 0; i < buckets.size(); i++) {
      for (auto iterator = buckets[i].data.begin();
           iterator != buckets[i].data.begin(); iterator++)
        map.insert(*iterator);
    }
    return map;
  }
};
};  // namespace thread_safe
};  // namespace cpstl

#endif
