/**
 * Segment tree data structure implementation
 * Copyright (C) 2020  Vincenzo Palazzo vincenzopalazzodev@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
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
    inline void assert_equal(std::string name_test, T aspected, T actual)
    {
        std::cout << BOLDWHITE << "|------------ TEST " << name_test << " -------------------|" << RESET << "\n";
        if (aspected == actual) {
            std::cout << BOLDGREEN << name_test  << " PASSED" << RESET << "\n";
            return;
        }
        std::cout << BOLDRED;
        std::cout << name_test  << " FAILED" << "\n";
        std::cout << "Aspected " << aspected << " but received " << actual << "\n";
    }

    template<typename T>
    inline void assert_equal(std::string name_test, std::vector<T> const &aspected, std::vector<T> const &actual)
    {
        std::cout << BOLDWHITE << "|------------ TEST " << name_test << " -------------------|" << RESET << "\n";
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
    }
}
