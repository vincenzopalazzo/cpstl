//
// Created by vincent on 9/23/20.
//
#include <iostream>
#include <vector>
#include "BinarySearch.h"

int main()
{
    std::vector<int> inputs = {0, 4, 3, 2, 32, 5, 6, 52, 43, 13};

    std::cout << "Input ";
    for (auto elem : inputs)
        std::cout << elem << " ";
    std::cout << std::endl;


    std::cout << "search 52" << std::endl;
    int index = cpstl::binary_search(inputs, 52, 0, inputs.size() - 1);
    std::cout << "Index found is: " << index << std::endl;
    if (index != -1)
        std::cout << "Element is: " << inputs.at(index) << std::endl;

    std::cout << "search 100" << std::endl;
    index = cpstl::binary_search(inputs, 100, 0, inputs.size() - 1);
    std::cout << "Index found is: " << index << std::endl;
    if (index != -1)
        std::cout << "Element is: " << inputs.at(index) << std::endl;
}