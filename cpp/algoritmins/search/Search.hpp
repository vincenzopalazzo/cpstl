/**
 * Search algorithm's C++ implementation
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
#include <vector>

namespace cpstl {

template <class T, typename R>
class Search {
 protected:
  static R _binary_search(std::vector<T> const &inputs, T key,
                          std::size_t start, std::size_t end) {
    if (start > end) return -1;
    // We go to te middle of algorithm
    auto middle_pos = start + (end - start) / 2;
    if (inputs[middle_pos] > key) {
      // sub array [start, middle_pos]
      return _binary_search(inputs, key, start, middle_pos - 1);
    } else if (inputs[middle_pos] < key) {
      // sub array [middle_pos - end]
      return _binary_search(inputs, key, middle_pos + 1, end);
    }
    return middle_pos;
  }

 public:
  static R binary_search(std::vector<T> const &inputs, T key) {
    return _binary_search(inputs, key, 0, inputs.size() - 1);
  }

  static R binary_search(std::vector<T> const &inputs, T key, std::size_t start,
                         std::size_t end) {
    return _binary_search(inputs, key, start, end);
  }

  static R exponential_search(std::vector<T> const &inputs, T key) {
    if (inputs[0] == key) return 0;
    R size_sub_array = 1;
    while (size_sub_array < inputs.size() && inputs[size_sub_array] < key) {
      size_sub_array *= 2;
    }
    R start = size_sub_array;
    R end = std::min(size_sub_array, static_cast<R>(inputs.size() - 1));
    return _binary_search(inputs, key, start, end);
  }
};
};  // namespace cpstl
