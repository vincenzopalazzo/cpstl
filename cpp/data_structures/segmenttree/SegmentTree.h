//
// Created by vincent on 10/27/20.
//

#ifndef RBTREE_SEGMENTTREE_H
#define RBTREE_SEGMENTTREE_H

#include <vector>

namespace cpst
{
    template <class T>
    class SegmentTree
    {
    private:
        std::vector<T> structure;

        void build_structure(std::vector<T> const &inputs, int left_index, int right_index);

        void build_structure_procedure(const std::vector<T> &inputs, int start_index, int left_index, int right_index);

        int range_query_subroutine(int start_index, int end_index);

        inline int left_child_index(const int index)
        {
            // (2 * index) + 1
            return index << 1;
        }

        inline int right_child_index(const int index)
        {
            //(2 * index) + 2;
            return (index << 1) + 1;
        }
    public:

        /**
         * This constructor bring a normal vector and build under the hood the
         * the segment tree with binary heap implementation
         * @param inputs
         */
        SegmentTree(std::vector<T> const &inputs){
            int size = inputs.size();
            structure = std::vector<T>(size * 4);
            build_structure(inputs, 0, size);
        }

        /**
         * This constructor is for the dynamic segment tree
         * not implemented yest inside this structure
         * @param size
         */
        SegmentTree(const int size){
            structure = std::vector<T>(size * 4);
        }

        virtual ~SegmentTree() {
            structure.clear();
        }

        int range_query(int start_index, int end_index);

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
