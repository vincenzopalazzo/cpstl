//
// Created by vincent on 9/23/20.
//
#include <iostream>
#include <vector>
#include <cmath>
#include "Search.h"

int main()
{
    std::vector<int> inputs;

    for (int i = 0; i < 30; i++)
        inputs.push_back(std::pow(2, i));

    std::cout << "Input ";
    for (auto elem : inputs)
        std::cout << elem << " ";
    std::cout << std::endl;


    std::cout << "search " << inputs.at(2) << std::endl;
    int index = cpstl::binary_search(inputs, inputs.at(2), 0, inputs.size() - 1);
    std::cout << "Index found is: " << index << std::endl;
    if (index != -1)
        std::cout << "Element is: " << inputs.at(index) << std::endl;

    std::cout << "search 100" << std::endl;
    index = cpstl::binary_search(inputs, inputs.at(inputs.size() - 2), 0, inputs.size() - 1);
    std::cout << "Index found is: " << index << std::endl;
    if (index != -1)
        std::cout << "Element is: " << inputs.at(index) << std::endl;

    std::cout << "-------- Exponential Searching -------\n";
    std::cout << "search " << inputs.at(2) << std::endl;
    index = cpstl::exponential_search(inputs, inputs.at(2));
    std::cout << "Index found is: " << index << std::endl;
    if (index != -1)
        std::cout << "Element is: " << inputs.at(index) << std::endl;
    std::cout << "search " << inputs.at(inputs.size() - 2) << std::endl;
    index = cpstl::exponential_search(inputs, inputs.at(inputs.size() - 2));
    std::cout << "Index found is: " << index << std::endl;
    if (index != -1)
        std::cout << "Element is: " << inputs.at(index) << std::endl;

}