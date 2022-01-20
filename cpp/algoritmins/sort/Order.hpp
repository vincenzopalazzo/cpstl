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
#ifndef ORDER_HPP
#define ORDER_HPP

#include <assert.h>

#include <random>
#include <unordered_map>
#include <vector>

namespace cpstl {

template <class T = int>
class Order {
 protected:
  /**
   * The procedure is called inside the main function merge_sort,
   * this permitted to subdivide the function inside the procedure and
   * is easy change the function with somethings else to resolve some
   * competitive programming problem.
   *
   * P.S: The source of this code is the teorical book on algorithms
   * @tparam T is a generic type, can be all type numeric that we want, by
   * default is supported only the int (for the moment) but your can extend it.
   * @param inputs Is a array or sequence of number that we want sort.
   * @param p an array index <= of q
   * @param q an array index < of r but >= or p
   * @param r an array index < of p and q.
   */
  void merge(std::vector<T> &inputs, int p, int q, int r) {
    assert(!inputs.empty());
    assert(p >= 0);
    assert(r >= 0);
    assert(q >= 0);

    auto n1 = q - p + 1;
    auto n2 = r - q;
    std::vector<T> sub_arr_left;
    sub_arr_left.reserve(n1);
    std::vector<T> sub_arr_right;
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

  std::size_t partition(std::vector<T> &inputs, int p, int r) {
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

  std::size_t randomize_partition(std::vector<T> &inputs, int p, int r) {
    std::random_device rd;
    std::mt19937 mt(rd());
    auto generator = std::uniform_int_distribution<int>(0, inputs.size() - 1);
    auto pivot = generator(mt);
    std::swap(inputs[pivot], inputs[r]);
    return partition(inputs, p, r);
  }

 public:
  /**
   * This method implement the merge sort algorithm, and the list below describe
   * the parameters
   *
   * @param inputs: inputs element to sort
   * @param p: start index, the first value should be 0
   * @param r end index, the first value should be a inputs.size() - 1
   */
  void merge_sort(std::vector<T> &inputs, int p, int r) {
    if (p < r) {
      int q = (p + r) / 2;
      merge_sort(inputs, p, q);
      merge_sort(inputs, q + 1, r);
      merge(inputs, p, q, r);
    }
  }

  /**
   * This procedure sort the input array with a standard quick sort
   * implementation.
   *
   * @tparam T type of element in the input
   * @param inputs input array
   */
  void quick_sort(std::vector<T> &inputs, int p, int r) {
    if (p < r) {
      auto middle = partition(inputs, p, r);
      quick_sort(inputs, p, middle - 1);
      quick_sort(inputs, middle + 1, r);
    }
  }

  /**
   * The randomize quick sort that take randomly the pivot before
   * start to partition the array.
   *
   * In the benchmark we can see how we solve the solution very fast
   * when the array is sorted.
   */
  void randomize_quick_sort(std::vector<T> &inputs, int p, int r) {
    if (p < r) {
      auto middle = randomize_partition(inputs, p, r);
      quick_sort(inputs, p, middle - 1);
      quick_sort(inputs, middle + 1, r);
    }
  }


  /**
   * Implementation of the counting sort algorithm, and
   * the time complexity of the algorithm is O(N + K) where:
   * K is the number of element insert inside the array distinct
   * N is the size of the input array.
   *
   * We are close to linear time complexity when K <= N, in this case
   * the complexity is O(N)
   */
  void counting_sort(std::vector<T> &input, T min_elem, T max_elem) {
    // This make sure that Time complexity is O(1) and
    // space complexity is O(N ^ 2) because we need to store 2
    // integer for a single element in the array
    std::unordered_map<T, T> count_map;

    for (auto const &elem : input) {
      if (count_map.find(elem) != count_map.end()) {
        auto value = count_map.at(elem);
        count_map.insert(std::make_pair(elem, value + 1));
      } else {
        count_map.insert(std::make_pair(elem, 1));
      }
    }

    std::size_t start = 0;
    for (std::size_t i = min_elem; i <= max_elem; i++) {
      auto iterator = count_map.find(i);
      if (iterator == count_map.end()) continue;
      auto elem = iterator->second;
      for (std::size_t j = 0; j < elem; j++) {
        input[start] = i;
        start++;
      }
    }
  }

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
  };  // namespace cpstl
};
};  // namespace cpstl

#endif
