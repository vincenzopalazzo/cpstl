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
#include <vector>

namespace cpstl {

/**
 * This method implement the merge sort algorithm, and the list below describe
 * the parameters
 *
 * @param inputs: inputs element to sort
 * @param p: start index, the first value should be 0
 * @param r end index, the first value should be a inputs.size() - 1
 */
template <typename T>
void merge_sort(std::vector<T> &inputs, int p, int r);

/**
 * This procedure sort the input array with a standard quick sort
 * implementation.
 *
 * @tparam T type of element in the input
 * @param inputs input array
 */
template <typename T>
void quick_sort(std::vector<T> &inputs, int p, int r);

template <typename T>
void randomize_quick_sort(std::vector<T> &inputs, int p, int r);

template <typename T>
void odd_even_sort(std::vector<T> &inputs, int p, int r);


template <typename T>
void radix_sort(std::vector<int> &inputs, int p, int r);

}  // namespace cpstl
