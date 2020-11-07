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
#include <iostream>
#include "SegmentTree.h"

using namespace cpst;


template<class T>
void SegmentTree<T>::build_structure(int left_index, int right_index)
{
    build_structure_procedure(1, left_index, right_index - 1);
}

template<class T>
void SegmentTree<T>::build_structure_procedure(int start_index, int left_index, int right_index)
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

template<class T>
int SegmentTree<T>::range_query(int start_index, int end_index) {
    return range_query_subroutine(1, 0, origin.size() - 1, start_index, end_index);
}

template<class T>
int SegmentTree<T>::range_query_subroutine(int start_index, int left_index_now, int right_index_now, int query_left, int query_right)
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

template<class T>
void SegmentTree<T>::update(int at, T value)
{
   update_subroutine(1, 0, origin.size() - 1, at, value);
}

template<class T>
void SegmentTree<T>::update_subroutine(int start_index, int left_index, int right_index, int pos, T new_value)
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
        std::cout << "Update at " << start_index << " with cavalue " << structure[start_index] << "\n";
    }
}

template<class T>
SegmentTree<T>::SegmentTree(std::vector<T> &origin): origin(origin)
{
    int size = origin.size();
    structure = std::vector<T>(size * 4);
    origin = origin;
    build_structure(0, size);
}

template<class T>
SegmentTree<T>::~SegmentTree()
{
    structure.clear();
}


template class cpst::SegmentTree<int>;