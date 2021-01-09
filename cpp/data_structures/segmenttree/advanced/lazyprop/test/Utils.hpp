/**
 * Segment tree data structure implementation
 * Copyright (C) 2020-2021  Vincenzo Palazzo vincenzopalazzodev@gmail.com
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
#include <bits/stdc++.h>
#include "colors.h"

using namespace std;

namespace cpstl {

    template<typename T>
    inline void print_vector(std::vector<T> const &inputs)
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
}
// Last update 9/1/2021