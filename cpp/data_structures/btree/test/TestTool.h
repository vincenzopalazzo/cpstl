//
// Created by vincent on 11/8/20.
//
#include <iostream>
#include <vector>
#include "colors.h"

namespace cpstl {

    /**
    void assert_is_true(std::string name_test, bool condition)
    {
        if (condition) {
            std::cout << BOLDGREEN << name_test  << " PASSED" << RESET << "\n";
            return;
        }
        std::cout << BOLDRED << name_test  << " FAILED" << RESET << "\n";
    }
    **/
    template<typename T>
    void assert_equal(std::string name_test, T aspected, T actual)
    {
        std::cout << BOLDWHITE << "|------------ TEST " << name_test << " -------------------|" << RESET << "\n";
        if (aspected == actual) {
            std::cout << BOLDGREEN << name_test  << " PASSED" << RESET << "\n";
            return;
        }
        std::cout << BOLDRED;
        std::cout << name_test  << " FAILED" << "\n";
        std::cout << "Aspected " << aspected << " but received " << actual << "\n";
        std::cout << BOLDWHITE << "\n|------------ END " << name_test << " -------------------|" << RESET << "\n\n";
    }

    template<typename T>
    void assert_equal(std::string name_test, std::vector<T> const &aspected, std::vector<T> const &actual)
    {
        std::cout << BOLDWHITE << "\n|------------ TEST " << name_test << " -------------------|" << RESET << "\n";
        if (aspected.size() != actual.size()) {
            std::cout << BOLDRED;
            std::cout << name_test  << " FAILED" << "\n";
            std::cout << "Aspected size is " << aspected.size() << " but it is different from how I received " << actual.size() << "\n";
            std::cout << RESET;
            return;
        }
        for (int i = 0; i < aspected.size(); i++) {
            if (aspected.at(i) != actual.at(i)) {
                std::cout << BOLDRED;
                std::cout << name_test  << " FAILED" << "\n";
                std::cout << "Aspected vector at postion " << i << " has different value from the actual vector" << "\n";
                std::cout << "Asspected value is: " << aspected.at(i) << " and the actual value is " << actual.at(i) << "\n";
                std::cout << RESET;
                return;
            }
        }
        std::cout << BOLDGREEN << name_test  << " PASSED" << RESET << "\n";
        std::cout << BOLDWHITE << "\n|------------ END " << name_test << " -------------------|" << RESET << "\n";
    }
}
