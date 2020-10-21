//
// Created by vincent on 10/21/20.
//

#ifndef BINARYSEARCHDEMO_ORDER_H
#define BINARYSEARCHDEMO_ORDER_H

#include <vector>

namespace cpstl {

    /**
     * This method implement the merge sort algorithm, and the list below describe the parameters
     *
     * @param inputs: inputs element to sort
     * @param p: start index, the first value should be 0
     * @param r end index, the first value should be a inputs.size() - 1
     */
    template <typename T>
    void merge_sort(std::vector<T> &inputs, int p, int r);

}

#endif //BINARYSEARCHDEMO_ORDER_H
