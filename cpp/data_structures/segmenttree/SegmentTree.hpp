/**
 * Segment tree data structure implementation
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
template <class T>
class SegmentTree {
 private:
  std::vector<T> &origin;
  std::vector<T> structure;

  /**
   * This function is used build the segment tree with a binary heap
   * implementation, and it use the origin array stored in the class.
   * @tparam T is the type of structure, usually it is a int or another numeric
   * type
   * @param left_index the left index of the range
   * @param right_index the right index of the range
   */
  void build_structure(int left_index, int right_index) {
    build_structure_procedure(1, left_index, right_index - 1);
  }
  /**
   * This is the sub procedure that help the build_structure procedure to make
   * the logic inside the segment tree
   * @tparam T is the type of structure, usually it is a int or another numeric
   * type
   * @param start_index
   * @param left_index
   * @param right_index
   */
  void build_structure_procedure(std::size_t start_index, std::size_t left_index,
                                 std::size_t right_index) {
    if (left_index == right_index) {
      // Leaf node will have a single element
      structure[start_index] = left_index;
      return;
    }
    auto middle_point = (left_index + right_index) / 2;
    auto left_child = left_child_index(start_index);
    auto right_child = right_child_index(start_index);
    build_structure_procedure(left_child, left_index, middle_point);
    build_structure_procedure(right_child, middle_point + 1, right_index);
    // Internal node will have the sum of both of its children
    auto segment_left = structure[left_child];
    auto segment_right = structure[right_child];
    structure[start_index] = (origin[segment_left] <= origin[segment_right])
                                 ? segment_left
                                 : segment_right;
  }

  std::size_t range_query_subroutine(std::size_t start_index, std::size_t left_index_now,
                             std::size_t right_index_now, std::size_t query_left,
                             std::size_t query_right) {
    if (query_left > right_index_now || query_right < left_index_now)
      return -1;  // outside the range
    if (left_index_now >= query_left && right_index_now <= query_right)
      return structure[start_index];  // range represented by a node is
                                      // completely inside the given range
    // range represented by a node is partially inside and partially outside the
    // given range
    auto middle_point = (left_index_now + right_index_now) / 2;
    auto left_child = left_child_index(start_index);
    auto right_child = right_child_index(start_index);
    auto left_segment = range_query_subroutine(
        left_child, left_index_now, middle_point, query_left, query_right);
    auto right_segment =
        range_query_subroutine(right_child, middle_point + 1, right_index_now,
                               query_left, query_right);
    if (left_segment == -1) return right_segment;
    if (right_segment == -1) return left_segment;
    return (origin[left_segment] <= origin[right_segment]) ? left_segment
                                                           : right_segment;
  }

  void update_subroutine(std::size_t start_index, std::size_t left_index, std::size_t right_index,
                         std::size_t pos, T new_value) {
    if (left_index == right_index) {
      origin[pos] = new_value;
      structure[start_index] = pos;
    } else {
      auto middle_point = (left_index + right_index) / 2;
      auto left_child = left_child_index(start_index);
      auto right_child = right_child_index(start_index);
      if (pos <= middle_point) {
        update_subroutine(left_child, left_index, middle_point, pos, new_value);
      } else {
        update_subroutine(right_child, middle_point + 1, right_index, pos,
                          new_value);
      }
      auto segment_left = structure[left_child];
      auto segment_right = structure[right_child];
      structure[start_index] = (origin[segment_left] <= origin[segment_right])
                                   ? segment_left
                                   : segment_right;
    }
  }

  inline std::size_t left_child_index(std::size_t const index) {
    // return index << 1;
    return index * 2;
  }

  inline std::size_t right_child_index(std::size_t const index) {
    // return (index << 1) + 1;
    return (index * 2) + 1;
  }

 public:
  SegmentTree(std::vector<T> &origin) : origin(origin) {
    auto size = origin.size();
    structure = std::vector<T>(size * 4);
    origin = origin;
    build_structure(0, size);
  }

  virtual ~SegmentTree() { structure.clear(); }

  std::size_t range_query(std::size_t start_index, std::size_t end_index) {
    return range_query_subroutine(1, 0, origin.size() - 1, start_index,
                                  end_index);
  }

  /**
   * This is the sub procedure that help the build_structure procedure to make
   * the logic inside the segment tree
   * @param at: it is the position in the original array, the function change
   * the value also in the original array
   * @param new_value the value that we want override in position at.
   */
  void update(std::size_t const at, T value) {
    update_subroutine(1, 0, origin.size() - 1, at, value);
  }

  inline T get_elem(std::size_t const at) { return origin[at]; }
};
};  // namespace cpstl
