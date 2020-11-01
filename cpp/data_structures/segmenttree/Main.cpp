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
    cout << "Inputs: [";
    for (int i = 0; i < inputs.size(); i++) {
        if (i == inputs.size() - 1) {
            cout << "(" << i + 1 << ", " << inputs[i] << ")" << "]";
            continue;
        }
        cout << "(" << i + 1 << ", " << inputs[i] << "), ";
    }
    cout << "\n";
    auto segment_tree = SegmentTree<int>(inputs);
    int index = segment_tree.range_query(4, 6);
    cout << "Range (4, 6) -> (" << index + 1 << ", " << inputs[index] << ")"  << "\n";
    assert(inputs[index] == 11);

    index = segment_tree.range_query(1, 3);
    cout << "Range (1, 3) -> (" << index + 1 << ", " << inputs[index] << ")"  << "\n";
    assert(inputs[index] == 13);

    std::cout << "=========== TEST CASES PASSED ==========" << "\n";
    return EXIT_SUCCESS;
}