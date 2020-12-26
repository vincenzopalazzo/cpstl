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
#include <vector>
#include <iostream>
#include "test/Utils.hpp"

namespace cpstl
{
    template <typename T>
    struct Node {
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        T value;

        Node(std::shared_ptr<Node> left, std::shared_ptr<Node> right) : left(left), right(right), value(0) {
            if (left) value = left->value;
            if (right) value = right->value;
        }
        Node(T value) : left(nullptr), right(nullptr), value(value) {}
    };

    template <class T>
    class PersistentSegmentTree
    {
    protected:
        std::shared_ptr<Node<T>> root;
        std::vector<T> &origin;
        std::vector<std::shared_ptr<Node<T>>> history;

        /**
         * This function is used build the segment tree with a binary heap
         * implementation, and it use the origin array stored in the class.
         * @tparam T is the type of structure, usually it is a int or another numeric type
         * @param left_index the left index of the range
         * @param right_index the right index of the range
         */
        std::shared_ptr<Node<T>> build_structure(int left_index, int right_index)
        {
            return build_structure_procedure(left_index, right_index);
        }

        /**
         * This is the sub procedure that help the build_structure procedure to make the logic inside the segment tree
         * this version store inside the node of Segment Tree the value and not the index of the value
         * @tparam T is the type of structure, usually it is a int or another numeric type
         * @param start_index
         * @param left_index
         * @param right_index
         */
        std::shared_ptr<Node<T>> build_structure_procedure(int left_index, int right_index)
        {
            if (left_index >= right_index) {
                // Leaf node will have a single element
                return std::make_shared<Node<T>>(origin[left_index]);;
            }
            int middle_point = (left_index + right_index) / 2;
            auto node_left = build_structure_procedure(left_index, middle_point);
            auto node_right = build_structure_procedure(middle_point + 1, left_index);
            return std::make_shared<Node<T>>(node_left, node_right);
        }

        int range_query_subroutine(std::shared_ptr<Node<T>> &node, int left_index_now, int right_index_now, int query_left, int query_right)
        {
            // outside the range
            if (query_left > right_index_now || query_right < left_index_now)  return -1;
            // range represented by a node is completely inside the given range
            if (left_index_now == query_left && right_index_now == query_right)  return root->value;
            // range represented by a node is partially inside and partially outside the given range
            int middle_point = (left_index_now + right_index_now) / 2;
            int left_segment = range_query_subroutine(node->left, left_index_now, middle_point,
                                                      query_left, std::min(query_right, middle_point));
            int right_segment = range_query_subroutine(node->right, middle_point + 1, right_index_now,
                                                       std::max(query_left, middle_point + 1), query_right);
            if (left_segment == -1) return right_segment;
            if (right_segment == -1) return left_segment;
            return (left_segment <= right_segment) ? left_segment : right_segment;
        }

        /**
         * Perform the real update of the update_range operation,
         * @param start_index: Start index, at the starting point this is 1
         * @param left_index: At the starting point it is the first position of the original array, so 0.
         * @param right_index: At the starting point it is the last position of the original array, so size - 1
         * @param from: The start index where start to update original array
         * @param to: The end index where stop to update original array
         * @param new_val: The value to sum to each position of the range in the original array.
         */
        std::shared_ptr<Node<T>> update_range_subroutine(std::shared_ptr<Node<T>> &node, int left_index, int right_index, int pos, T new_val)
        {
            if(left_index == right_index) {
                return std::make_shared<Node<T>>(new_val);
            }
            int middle_point = (left_index + right_index) / 2;
            if (pos <= middle_point) {
                auto left_node = update_range_subroutine(node->left, left_index, middle_point, pos, new_val);
                return std::make_shared<Node<T>>(left_node, node->right);
            }
            auto right_node = update_range_subroutine(node->right, middle_point + 1, right_index, pos, new_val);
            return std::make_shared<Node<T>>(node->left, right_node);
        }

    public:
        PersistentSegmentTree(vector<T> &origin) : origin(origin) {
            int size = origin.size();
            origin = origin;
            root = build_structure(0, size);
            history = std::vector<std::shared_ptr<Node<T>>>();
            history.push_back(root);
        }

        virtual ~PersistentSegmentTree()
        {
            root.reset();
            history.clear();
        }

        int range_query(int start_index, int end_index)
        {
            return range_query_subroutine(root, 0, origin.size(), start_index, end_index);
        }

        /**
         * This procedure update the value stored inside the structure in one single position, this use the
         * update_range_subroutine with from == to == at; to run the procedure update
         * @param at: it is the position in the original array, the function change the value also in the original array
         * @param new_value the value that we want override in position at.
         */
        void update(int at, T value)
        {
            auto new_root = update_range_subroutine(root, 0, origin.size(), at, value);
            history.push_back(new_root);
            root = new_root;
        }
    };
};