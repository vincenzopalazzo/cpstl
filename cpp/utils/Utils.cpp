#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "colors.h"

using namespace std;

namespace cpstl {

    template<typename T>
    void print_vector(std::vector<T> const &inputs)
    {
        std::cout << BOLDYELLOW;
        std::cout << "Inputs: [";
        for (int i = 0; i < inputs.size(); i++) {
            if (i == inputs.size() - 1) {
                std::cout << inputs[i] << "]";
                continue;
            }
            cout << inputs[i] << ", ";
        }
        cout << "\n";
        cout << RESET;
    }

    /**
     * This procedure is wrote to load data from the test data
     * download from the https://www.hackerrank.com/
     * @tparam T type of vector
     * @return return a single vector.
     */
    template<typename T>
    std::vector<T> load_input_from_string(std::string &input_string)
    {
        string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
            return x == y and x == ' ';
        });

        input_string.erase(new_end, input_string.end());

        while (input_string[input_string.length() - 1] == ' ') {
            input_string.pop_back();
        }

        vector<string> splits;
        char delimiter = ' ';

        size_t i = 0;
        size_t pos = input_string.find(delimiter);

        while (pos != string::npos) {
            splits.push_back(input_string.substr(i, pos - i));

            i = pos + 1;
            pos = input_string.find(delimiter, i);
        }

        splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

        return splits;
    }
}