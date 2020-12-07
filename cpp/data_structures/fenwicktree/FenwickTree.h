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

        int indexing(int index)
        {
            return index& -index;
        }

    public:
        BTreeIndex(const std::vector<T> &structure)
        {
            this->structure.reserve(structure.size() + 1);
            this->structure[0] = 0;
            for (int i = 0; i < structure.size(); i++) {
                this->structure[i + 1] = structure[i];
            }

            int at = 1;
            while (at < this->structure.size()) {
                int at_tree = indexing(at);
                this->structure[at_tree] += this->structure[at];
                at += indexing(at);
            }
        }

        BTreeIndex(int size)
        {
            structure = std::vector<T>(size + 1);
        }

        /**
         * This method give the possibility to insert a new value inside the tree at the position at
         * @param value The new value that I want insert
         * @param at The position of the tree that I want insert the value.
         *
         * This function override the previous value inside the tree
         */
        void update(T const &value, int at)
        {
            assert(at > 0 && "The position inside the array should be greater than 0");
            while (at < structure.size()) {
                structure[at] += value;
                at += indexing(at);
            }
        }

        /**
         * This methods calculate the sum of the path from begin to end with these value included
         * @param begin Fist element that I want calculate the prefix sum
         * @param end Last element that I want calculate the prefix sum
         * @return return the prefix sum of the array A[begin, end]
         */
        T sum(int begin, int end)
        {
            assert(begin >= 0 && end >= 0);
            T sum = 0;
            int at = end;
            while (at > begin) {
                sum += structure[at];
                at &= at - 1;
                //at -= indexing(at);
            }
            return sum;
        }

        /**
         * This method give the possibility to calculate the value from 0 to end;
         * @param end: is the final value that you want calculate the "sum" (it is included)
         * @return the sum of the subarray A[0, end]
         */
        T sum(int end)
        {
            assert(end >= 0);
            T sum = 0;
            int at = end;
            while (at > 0) {
                sum += structure[at];
                at &= at -1;
                //at -= indexing(at);
            }
            return sum;
        }

        /**
         * @return return the position of the minimum element
         */
        int min(T const value)
        {
            assert(false && "Not implemented yet");
        }

        /**
         * @return return the position of the maximum element;
         */
        int max(T const value)
        {
            assert(false && "Not implemented yet");
        }

    };
}

#endif //FENWICKTREE_FENWICKTREE_H
