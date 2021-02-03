/**
 * Sort algorithm's C++ implementation
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
#include "Order.hpp"

#include <cassert>
#include <iostream>

using namespace std;

namespace cpstl {

/**
 * The procedure is called inside the main function merge_sort,
 * this permitted to subdivide the function inside the procedure and
 * is easy change the function with somethings else to resolve some competitive
 * programming problem.
 *
 * P.S: The source of this code is the teorical book on algorithms
 * @tparam T is a generic type, can be all type numeric that we want, by default
 * is supported only the int (for the moment) but your can extend it.
 * @param inputs Is a array or sequence of number that we want sort.
 * @param p an array index <= of q
 * @param q an array index < of r but >= or p
 * @param r an array index < of p and q.
 */
template <typename T>
void merge(vector<T> &inputs, int p, int q, int r) {
  assert(!inputs.empty());
  assert(p >= 0);
  assert(r >= 0);
  assert(q >= 0);

  int n1 = q - p + 1;
  int n2 = r - q;
  vector<T> sub_arr_left;
  sub_arr_left.reserve(n1);
  vector<T> sub_arr_right;
  sub_arr_right.reserve(n2);

  for (int i = 0; i < n1; i++) {
    sub_arr_left.push_back(inputs.at(p + i));
  }
  for (int i = 0; i < n2; i++) {
    sub_arr_right.push_back(inputs.at(q + i + 1));
  }

  int i = 0;
  int j = 0;
  int k = p;
  while (i < n1 && j < n2) {
    if (sub_arr_left[i] < sub_arr_right[j] && sub_arr_left.size() >= i) {
      inputs[k] = sub_arr_left[i];
      i++;
    } else if (sub_arr_right.size() >= j) {
      inputs[k] = sub_arr_right[j];
      j++;
    }
    k++;
  }

  // copy the remain elements inside the input
  while (i < n1) {
    inputs[k] = sub_arr_left[i];
    i++;
    k++;
  }
  // copy the remain elements inside the input
  while (j < n2) {
    inputs[k] = sub_arr_right[j];
    j++;
    k++;
  }
}

template <typename T>
void merge_sort(vector<T> &inputs, int p, int r) {
  if (p < r) {
    int q = (p + r) / 2;
    merge_sort(inputs, p, q);
    merge_sort(inputs, q + 1, r);
    merge(inputs, p, q, r);
  }
}
}  // namespace cpstl

// Type declaration
template void cpstl::merge_sort<int>(vector<int> &inputs, int p, int r);
