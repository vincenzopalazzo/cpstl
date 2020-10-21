//
// Created by vincent on 9/23/20.
//
#include <iostream>
#include <vector>
#include <cassert>
#include "Order.h"

using namespace std;
using namespace cpstl;

int main()
{
    vector<int> inputs = {3, 4, 5, 2, 1};
    merge_sort<int>(inputs, 0, inputs.size() - 1);

    for (auto elem : inputs)
        cout << elem << " ";
    cout << "\n";

    assert(inputs.at(0) == 1);
    assert(inputs.at(1) == 2);
    assert(inputs.at(2) == 3);
    assert(inputs.at(3) == 4);
    assert(inputs.at(4) == 5);

    return EXIT_SUCCESS;
}