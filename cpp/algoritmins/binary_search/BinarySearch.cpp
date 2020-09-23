//
// Created by vincent on 9/23/20.
//
#include "BinarySearch.h"

namespace cpstl {

    template <typename T>
    int binary_search(std::vector<T> const &inputs, T key, size_t start, size_t end)
    {
        if(start > end) return -1;
        // We go to te middle of algoriptm
        size_t middle_pos = start + (end - start) / 2;
        if (inputs.at(middle_pos) > key) {
            //sub array [0, middle_pos]
            return binary_search(inputs, key, start, middle_pos - 1);
        } else if (inputs.at(middle_pos) < key) {
            // sub array [middle_pos - input.size()]
            return binary_search(inputs, key, middle_pos + 1, end);
        }
        return middle_pos;
    }

}

template int cpstl::binary_search<int>(const std::vector<int> &inputs, int key, size_t start, size_t end);
template int cpstl::binary_search<float>(const std::vector<float> &inputs, float key, size_t start, size_t end);
template int cpstl::binary_search<double>(const std::vector<double> &inputs, double key, size_t start, size_t end);
template int cpstl::binary_search<long>(const std::vector<long> &inputs, long key, size_t start, size_t end);
