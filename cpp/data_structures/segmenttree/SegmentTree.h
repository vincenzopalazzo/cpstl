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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef RBTREE_SEGMENTTREE_H
#define RBTREE_SEGMENTTREE_H

#include <vector>

namespace cpstl
{
    template <class T>
    class SegmentTree
    {
    private:
        /**
         * This store the reference of the origin array to managed the update operation
         * and maintain the array in sync.
         *
         * ALERT this is correct for a c++ idea? it look like yes?
         */
        std::vector<T> &origin;
        std::vector<T> structure;

        /**
         * This function is used build the segment tree with a binary heap
         * implementation, and it use the origin array stored in the class.
         * @tparam T is the type of structure, usually it is a int or another numeric type
         * @param left_index the left index of the range
         * @param right_index the right index of the range
         */
        void build_structure(int left_index, int right_index)
        {
            build_structure_procedure(1, left_index, right_index - 1);
        }
        /**
         * This is the sub procedure that help the build_structure procedure to make the logic inside the segment tree
         * @tparam T is the type of structure, usually it is a int or another numeric type
         * @param start_index
         * @param left_index
         * @param right_index
         */
        void build_structure_procedure(int start_index, int left_index, int right_index)
        {
            if (left_index == right_index) {
                structure[start_index] = left_index;
                return;
            }
            int middle_point = (left_index + right_index) / 2;
            int left_child = left_child_index(start_index);
            int right_child = right_child_index(start_index);
            build_structure_procedure(left_child, left_index, middle_point);
            build_structure_procedure(right_child, middle_point + 1, right_index);
            int segment_left = structure[left_child];
            int segment_right = structure[right_child];
            structure[start_index] = (origin[segment_left] <= origin[segment_right]) ? segment_left : segment_right;
        }

        int range_query_subroutine(int start_index, int left_index_now, int right_index_now, int query_left, int query_right)
        {
            if (query_left > right_index_now || query_right < left_index_now)  return -1;
            if (left_index_now >= query_left || right_index_now <= query_right)  return structure[start_index];
            int middle_point = (left_index_now + right_index_now) / 2;
            int left_child = left_child_index(start_index);
            int right_child = right_child_index(start_index);
            int left_segment = range_query_subroutine(left_child, left_index_now, middle_point, query_left, query_right);
            int right_segment = range_query_subroutine(right_child, middle_point + 1, right_index_now, query_left, query_right);
            if (left_segment == -1 || right_segment == -1) {
                return left_segment == -1 ? right_segment : left_segment;
            }

            return  (origin[left_segment] <= origin[right_segment]) ? left_segment : right_segment;
        }

        void update_subroutine(int start_index, int left_index, int right_index, int pos, T new_value)
        {
            if (left_index == right_index) {
                origin[pos] = new_value;
                structure[start_index] = pos;
            } else {
                int middle_point = (left_index + right_index) / 2;
                int left_child = left_child_index(start_index);
                int right_child = right_child_index(start_index);
                if (pos <= middle_point) {
                    update_subroutine(left_child, left_index, middle_point, pos, new_value);
                }else {
                    update_subroutine(right_child, middle_point + 1, right_index, pos, new_value);
                }
                int segment_left = structure[left_child];
                int segment_right = structure[right_child];
                structure[start_index] = (origin[segment_left] <= origin[segment_right]) ? segment_left : segment_right;
            }
        }

        inline int left_child_index(const int index)
        {
            return index << 1;
        }

        inline int right_child_index(const int index)
        {
            return (index << 1) + 1;
        }
    public:

        SegmentTree(std::vector<T> &origin): origin(origin)
        {
            int size = origin.size();
            structure = std::vector<T>(size * 4);
            origin = origin;
            build_structure(0, size);
        }

        virtual ~SegmentTree()
        {
            structure.clear();
        }

        int range_query(int start_index, int end_index)
        {
            return range_query_subroutine(1, 0, origin.size() - 1, start_index, end_index);
        }

        /**
         * This is the sub procedure that help the build_structure procedure to make the logic inside the segment tree
         * @param at: it is the position in the original array, the function change the value also in the original array
         * @param new_value the value that we want override in position at.
         */
        void update(int at, T value)
        {
            update_subroutine(1, 0, origin.size() - 1, at, value);
        }

        inline int left_child(int x)
        {
            int left = left_child_index(x);
            return structure[left];
        }

        inline int right_child(int x)
        {
            int left = right_child_index(x);
            return structure[left];
        }

    };
};

#endif //RBTREE_SEGMENTTREE_H
