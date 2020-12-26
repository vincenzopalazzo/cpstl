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
#include <memory>

namespace cpstl
{
    template <typename T>
    struct Node {
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        T value;

        Node(std::shared_ptr<Node> left, std::shared_ptr<Node> right) : left(left), right(right), value(0) {
            T left_val, right_val = 0;
            if (left) left_val = left->value;
            if (right) right_val = right->value;
            value = (left_val <= right_val) ? left_val : right_val;
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

        std::shared_ptr<Node<T>> build_structure(int left_index, int right_index)
        {
            return build_structure_procedure(left_index, right_index);
        }

        std::shared_ptr<Node<T>> build_structure_procedure(int left_index, int right_index)
        {
            if (left_index == right_index) {
                // Leaf node will have a single element
                return std::make_shared<Node<T>>(origin[left_index]);;
            }
            int middle_point = (left_index + right_index) / 2;
            auto node_left = build_structure_procedure(left_index, middle_point);
            auto node_right = build_structure_procedure(middle_point + 1, right_index);
            return std::make_shared<Node<T>>(node_left, node_right);
        }

        int range_query_subroutine(std::shared_ptr<Node<T>> &node, int left_index, int right_index, int query_left, int query_right)
        {
            // outside the range
            if (query_left > query_right || !node)  return -1;
            // range represented by a node is completely inside the given range
            if (left_index == query_left && right_index == query_right)  return node->value;
            // range represented by a node is partially inside and partially outside the given range
            int middle_point = (left_index + right_index) / 2;
            int left_segment = range_query_subroutine(node->left, left_index, middle_point,
                                                      query_left, std::min(query_right, middle_point));
            int right_segment = range_query_subroutine(node->right, middle_point + 1, right_index,
                                                       std::max(query_left, middle_point + 1), query_right);
            if (left_segment == -1) return right_segment;
            if (right_segment == -1) return left_segment;
            return (left_segment <= right_segment) ? left_segment : right_segment;
        }

        std::shared_ptr<Node<T>> update_range_subroutine(std::shared_ptr<Node<T>> &node, int left_index, int right_index, int pos, T new_val)
        {
            if(left_index == right_index || !node) {
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
        PersistentSegmentTree(std::vector<T> &origin) : origin(origin) {
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

        void update(int at, T value)
        {
            auto new_root = update_range_subroutine(root, 0, origin.size(), at, value);
            history.push_back(new_root);
            root = new_root;
        }
    };
};