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
#include <random>

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

  auto n1 = q - p + 1;
  auto n2 = r - q;
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

  auto i = 0;
  auto j = 0;
  auto k = p;
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

template <typename T>
std::size_t partition(vector<T> &inputs, int p, int r) {
  auto pivot = inputs[r];
  auto i = p - 1;
  for (auto j = p; j <= r - 1; j++) {
    if (inputs[j] <= pivot) {
      i++;
      std::swap(inputs[i], inputs[j]);
    }
  }
  i++;
  std::swap(inputs[i], inputs[r]);
  return i;
}

template <typename T>
void quick_sort(std::vector<T> &inputs, int p, int r) {
  if (p < r) {
    auto middle = partition(inputs, p, r);
    quick_sort(inputs, p, middle - 1);
    quick_sort(inputs, middle + 1, r);
  }
}

template <typename T>
std::size_t randomize_partition(vector<T> &inputs, int p, int r) {
  std::random_device rd;
  std::mt19937 mt(rd());
  auto generator = std::uniform_int_distribution<int>(0, inputs.size() - 1);
  auto pivot = generator(mt);
  std::swap(inputs[pivot], inputs[r]);
  return partition(inputs, p, r);
}

template <typename T>
void randomize_quick_sort(std::vector<T> &inputs, int p, int r) {
  if (p < r) {
    auto middle = randomize_partition(inputs, p, r);
    quick_sort(inputs, p, middle - 1);
    quick_sort(inputs, middle + 1, r);
  }
}

template <typename T>
void odd_even_sort(std::vector<T> &inputs, int p, int r) {
  auto is_sorted = false;
  while (!is_sorted) {
    is_sorted = true;

    int start_odd;
    int start_even;
    if (p % 2 == 0) {
      start_odd = p + 1;
      start_even = p;
    } else {
      start_odd = p;
      start_even = p + 1;
    }
    // Bubble sort on odd element
    for (int i = start_odd; i < r - 1; i += 2) {
      if (inputs[i] > inputs[i + 1]) {
        std::swap(inputs[i], inputs[i + 1]);
        is_sorted = false;
      }
    }

    // Bubble Sort on even element
    for (int i = start_even; i < r - 1; i += 2) {
      if (inputs[i] > inputs[i + 1]) {
        std::swap(inputs[i], inputs[i + 1]);
        is_sorted = false;
      }
    }
  }
}


template <typename T>
void count_sort(std::vector<T> &inputs, int p, int r, int exp){
  int output[r]; 
  int i, count[10] = { 0 };
  for (i = p; i < r; i++)
    count[(inputs[i] / exp) % 10]++;
  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];
  for (i = r - 1; i >= p; i--) {
        output[count[(inputs[i] / exp) % 10] - 1] = inputs[i];
        count[(inputs[i] / exp) % 10]--;
    }
  for (i = p; i < r; i++)
        inputs[i] = output[i];
}

template <typename T>
T getMax(std::vector<T> inputs, int p, int r){
  auto mx=inputs[p];
  for(int i=p+1; i<r; i++){
    mx=max(mx,inputs[i]);
  }
  return mx;
}

template <typename T>
void radix_sort(std::vector<T> &inputs, int p, int r){
  auto mx = getMax<T>(inputs,p,r);
  for (int exp = 1; mx / exp > 0; exp *= 10)
        count_sort(inputs, p, r, exp);
}

}  // namespace cpstl

// Type declaration
template void cpstl::merge_sort<int>(vector<int> &inputs, int p, int r);
template void cpstl::quick_sort<int>(std::vector<int> &inputs, int p, int r);
template void cpstl::randomize_quick_sort<int>(std::vector<int> &inputs, int p,
                                               int r);
template void cpstl::odd_even_sort<int>(std::vector<int> &inputs, int p, int r);
template void cpstl::radix_sort<int>(std::vector<int> &inputs, int p, int r);
