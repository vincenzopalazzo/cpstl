//
// Created by vincent on 9/14/20.
//
#include <cstdlib>
#include <vector>
#include <fstream>
#include "../core/SolTest.h"
#include "../Utils.cpp"
#include "TestTool.cpp"

using namespace std;
using namespace cpstl;

void TEST_CASE_ONE()
{
    vector<int> inputs = {20, 90, 40, 90};
    int maximum_house = get_maximum_number_of_house<int, int>(inputs, 100);
    assert_equal("TEST_CASE_ONE", 2, maximum_house);
}

void TEST_CASE_TWO()
{
    vector<int> inputs = {30, 30, 10, 10};
    int maximum_house = get_maximum_number_of_house<int, int>(inputs, 50);
    assert_equal("TEST_CASE_TWO", 3, maximum_house);
}


void TEST_CASE_TREE()
{
    vector<int> inputs = {999, 999, 999};
    int maximum_house = get_maximum_number_of_house<int, int>(inputs, 300);
    assert_equal("TEST_CASE_TREE", 0, maximum_house);
}

int main()
{
    TEST_CASE_ONE();
    TEST_CASE_TWO();
    TEST_CASE_TREE();

    return EXIT_SUCCESS;
}