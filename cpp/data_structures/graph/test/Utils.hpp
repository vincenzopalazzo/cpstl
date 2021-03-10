/**
 * CPSTL Utils a collection of method to make common operation with C++
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */
#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>

#include <iostream>
#include <vector>

#include "colors.h"

using namespace std;

namespace cpstl {

struct Log {
  bool enable = false;

  Log(bool enable) : enable(enable) {}
};


  template <typename T>
  inline void print_vector(std::vector<T> const &inputs) {
    std::cout << BOLDYELLOW;
    std::cout << "Vector: [";
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


inline void cp_log(Log log, std::string message) {
  if (!log.enable) return;
  std::cout << BOLDYELLOW;
  std::cout << message;
  std::cout << "\n";
  std::cout << RESET;
}

template <typename T>
inline void cp_log(Log log, std::vector<T> const &inputs) {
  if (!log.enable) return;
  std::cout << BOLDYELLOW;
  print_vector(inputs);
  std::cout << RESET;
}

/**
 * This procedure is wrote to load data from the test data
 * download from the https://www.hackerrank.com/
 * @tparam T type of vector
 * @return return a single vector.
 */
template <typename T>
inline std::vector<T> load_input_from_string(std::string &input_string) {
  string::iterator new_end =
      unique(input_string.begin(), input_string.end(),
             [](const char &x, const char &y) { return x == y and x == ' '; });

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

  splits.push_back(
      input_string.substr(i, min(pos, input_string.length()) - i + 1));

  return splits;
}
}  // namespace cpstl
#endif
