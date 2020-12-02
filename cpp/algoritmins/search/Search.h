//
// Created by vincent on 9/23/20.
//

#ifndef RBTREE_BINARYSEARCH_H
#define RBTREE_BINARYSEARCH_H

#include <vector>

namespace cpstl {

    template <typename T>
    int binary_search(std::vector<T> const &inputs, T key, int start, int end)
    {
        if(start > end) return -1;
        // We go to te middle of algorithm
        int middle_pos = start + (end - start) / 2;
        if (inputs.at(middle_pos) > key) {
            //sub array [start, middle_pos]
            return binary_search(inputs, key, start, middle_pos - 1);
        } else if (inputs.at(middle_pos) < key) {
            // sub array [middle_pos - end]
            return binary_search(inputs, key, middle_pos + 1, end);
        }
        return middle_pos;
    }

    template <typename T>
    int exponential_search(std::vector<T> const &inputs, T key)
    {
        int size_sub_array = 1;
        while (size_sub_array < inputs.size() && inputs.at(size_sub_array) < key) {
            size_sub_array *= 2;
        }
        return binary_search(inputs, key, size_sub_array / 2, std::min(size_sub_array, static_cast<int>(inputs.size())));
    }
}

#endif //RBTREE_BINARYSEARCH_H
