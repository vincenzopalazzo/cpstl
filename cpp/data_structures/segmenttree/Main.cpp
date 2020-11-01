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

    for (int i = 0; i < inputs.size(); i++) {
        cout << "Left of " << inputs[i] << " is " << segment_tree.left_child(i) << "\n";
        cout << "Right of " << inputs[i] << " is " << segment_tree.right_child(i) << "\n";
    }


    std::cout << "=========== TEST CASES PASSED ==========" << "\n";
    return EXIT_SUCCESS;
}