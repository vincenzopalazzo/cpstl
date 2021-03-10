/**
 * Graph data structure implementation with adjacency list C++
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
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#include "test/Utils.hpp"

const cpstl::Log LOG(true);

namespace cpstl_internal {
template <class T>
class Node {
 public:
  std::vector<Node<T>> children;
  T value;

  Node() : value(INT_MAX) {}
  Node(T value) : value(value) {}

  void addNode(T value) {
    auto node = Node<T>(value);
    this->children.push_back(node);
  }
};
};  // namespace cpstl_internal

namespace cpstl {

template <class T>
class GraphList {
 private:
  std::vector<cpstl_internal::Node<T>> nodes;
  // this propriety means that the graph is an directed graph
  // but at the moment this is the only type of graph implemented
  // in the library
  bool directed;

  cpstl_internal::Node<T> *find_node(cpstl_internal::Node<T> &node, T value) {
    if (node.value == value) {
      return &node;
    }
    for (auto &child : node.children) {
      auto *found = find_node(child, value);
      if (found != nullptr) return found;
    }
    return nullptr;
  }

  void dfs_helper(cpstl_internal::Node<T> const &node, std::vector<T> &result) {
    result.push_back(node.value);
    std::vector<T> values;
    for (auto child : node.children) values.push_back(child.value);
    for (auto &other : node.children) dfs_helper(other, result);
  }

  void bfs_helper(cpstl_internal::Node<T> const &node, std::vector<T> &path) {
    std::deque<cpstl_internal::Node<T>> to_visit_queue;
    to_visit_queue.push_back(node);
    while (!to_visit_queue.empty()) {
      auto to_visit = to_visit_queue.front();
      to_visit_queue.pop_front();
      path.push_back(to_visit.value);
      for (auto child : to_visit.children) {
        to_visit_queue.push_back(child);
      }
    }
  }

 public:
  GraphList(bool directed) : directed(directed) {}

  /**
   * Here is reported the convention that are in a lot of book
   * the convention call a edge (u, v) that goes from U -> V and vice versa
   * the the graph is not directed.
   */
  void add_edge(T u, T v) {
    if (!nodes.empty()) {
      for (auto &node : nodes) {
        auto *found = find_node(node, u);
        if (found != nullptr) {
          found->addNode(v);
          return;
        }
      }
    }
    this->nodes.emplace_back(u);
    auto &node = this->nodes.back();
    node.addNode(v);
  }

  std::vector<std::vector<T>> dfs() {
    std::vector<std::vector<T>> paths;
    paths.reserve(nodes.size());
    for (auto &node : nodes) {
      std::vector<T> path;
      this->dfs_helper(node, path);
      paths.push_back(std::move(path));
    }
    return paths;
  }

  std::vector<std::vector<T>> bfs() {
    std::vector<std::vector<T>> paths;
    paths.reserve(nodes.size());
    for (auto node : nodes) {
      std::vector<T> path;
      this->bfs_helper(node, path);
      paths.push_back(std::move(path));
    }
    return paths;
  }
};
};  // namespace cpstl
