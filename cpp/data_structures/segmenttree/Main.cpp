//
// Created by vincent on 10/27/20.
//
#include <cstdlib>
#include <iostream>
#include <cassert>
#include "SegmentTree.h"

using namespace std;
using namespace cpst;

int main()
{
    std::cout << "============== TEST CASE 1 ==============" << "\n";
    vector<int> inputs = {18, 17, 13, 19, 15, 11, 20};
    auto segment_tree = SegmentTree<int>(inputs);
    cout << segment_tree.range_query(1, 2);
    assert(segment_tree.range_query(1, 2) == 35);


    std::cout << "=========== TEST CASES PASSED ==========" << "\n";
    return EXIT_SUCCESS;
}