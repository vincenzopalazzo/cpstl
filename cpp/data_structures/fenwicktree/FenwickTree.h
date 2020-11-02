//
// Created by vincent on 10/17/20.
//

#ifndef FENWICKTREE_FENWICKTREE_H
#define FENWICKTREE_FENWICKTREE_H

#include <vector>

namespace cpstl {

    template<class T>
    class BTreeIndex {

    private:
        std::vector<T> structure;

        int indexing(int index);

    public:
        BTreeIndex(const std::vector<T> &structure);
        BTreeIndex(int size);

        /**
         * This method give the possibility to insert a new value inside the tree at the position at
         * @param value The new value that I want insert
         * @param at The position of the tree that I want insert the value.
         *
         * This function override the previous value inside the tree
         */
        void update(T const &value, int at);

        /**
         * This methods calculate the sum of the path from begin to end with these value included
         * @param begin Fist element that I want calculate the prefix sum
         * @param end Last element that I want calculate the prefix sum
         * @return return the prefix sum of the array A[begin, end]
         */
        T sum(int begin, int end);

        /**
         * This method give the possibility to calculate the value from 0 to end;
         * @param end: is the final value that you want calculate the "sum" (it is included)
         * @return the sum of the subarray A[0, end]
         */
        T sum(int end);

        /**
         * @return return the position of the minimum element
         */
        int min(T const value);

        /**
         * @return return the position of the maximum element;
         */
        int max(T const value);

    };
}

#endif //FENWICKTREE_FENWICKTREE_H
