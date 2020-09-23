//
// Created by vincent on 9/23/20.
//

#ifndef RBTREE_BINARYSEARCH_H
#define RBTREE_BINARYSEARCH_H

#include <vector>

namespace cpstl {

    template <typename T>
    int binary_search(std::vector<T> const &inputs, T key, size_t start, size_t end);

}

#endif //RBTREE_BINARYSEARCH_H
