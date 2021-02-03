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
#include <benchmark/benchmark.h>

#include "../Order.hpp"

using namespace cpstl;

static void BM_CPSTL_MERGE_SORT(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) random_array.push_back(i);
    state.ResumeTiming();
    merge_sort(random_array, 0, random_array.size() - 1);
  }
}

static void BM_STL(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) random_array.push_back(i);
    state.ResumeTiming();
    std::sort(random_array.begin(), random_array.end());
  }
}

BENCHMARK(BM_CPSTL_MERGE_SORT)->Range(1 << 14, 1 << 18);
BENCHMARK(BM_STL)->Range(1 << 14, 1 << 18);

BENCHMARK_MAIN();
