//
// Created by vincent on 10/17/20.
//
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include "FenwickTree.h"

using namespace cpstl;

int main()
{
    auto tree = BTreeIndex<int>(5);
    tree.update(1, 1);
    tree.update(2, 2);
    tree.update(3, 3);
    tree.update(4, 4);
    tree.update(5, 5);
    std::cout << "------------- insert finisced -----------\n";
    assert(tree.sum(1) == 1);
    assert(tree.sum(2) == 3);
    assert(tree.sum(3) == 6);

    std::cout << "TEST SUITE PASSED\n";
    return EXIT_SUCCESS;
}