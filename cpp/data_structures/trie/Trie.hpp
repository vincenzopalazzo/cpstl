/**
 * Trie implementation in C++ 14
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
#ifndef TRIE_HPP
#define TRIE_HPP

#include <cassert>
#include <climits>
#include <memory>
#include <vector>

namespace cpstl {

template <class T = char>
class Trie;

enum class ALPHABETH {
    EN = 26
};

namespace internal {

template <class T = char>
class Node {
 private:
  bool nil;
  T value;
  //
  std::vector<Node<T>> children;
  friend cpstl::Trie<T>;

 public:
  Node(ALPHABETH alphabet = ALPHABETH::EN, bool nil = false):
    nil(nil), value('a'), children((int)alphabet, Node<>(alphabet, nil)) {}

  Node(T const &value, ALPHABETH alphabet = ALPHABETH::EN)
    : Node<>(alphabet), value(value) {}
};
};  // namespace internal

/**
 * Core implementation of the Trie.
 *
 * This class provide the API to resolve prefix search in a dictionary.
 *
 * author: https://github.com/vincenzopalazzo
 */
template <class T>
class Trie {
 private:
  std::shared_ptr<internal::Node<T>> root;
  ALPHABETH alphabet;
  char start_char;

  void insert_helper(std::shared_ptr<internal::Node<T>> node, char character) {
    //TODO implement this helper
  }

 public:
  Trie(ALPHABETH alphabet = ALPHABETH::EN, char start_chari = 'a'):
    alphabet(alphabet), start_char(start_char) {
    root = std::make_shared<internal::Node<T>>(internal::Node<T>(alphabet, true));
  }

  /**
   * Insert a word inside the Trie data structure.
   */
  void insert(std::string const &word) {
    bool alread_in = contains_prefix(word);
    if (alread_in)
      return;
    //TODO: insert the word inside the trie
  }

  /**
   * insert a list of words inside the Trie data structure.
   */
  void insert(std::vector<std::string> const &words) { }

  /**
   * Check if the Trie contains the prefix.
   */
  bool contains_prefix(std::string const &prefix) {
    return false;
  }

  /**
   * Given a prefix, return the first occurence with this prefix.
   */
  std::string get_with_profix(std::string const &prefix) {
    return prefix;
  }

  /**
   * Given a prefix, return all the words contained that start with the prefix.
   */
  std::vector<std::string> get_with_prefix(std::string const &prefix) {
    return {};
  }
};

};  // namespace cpstl

#endif
