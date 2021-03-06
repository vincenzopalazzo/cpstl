/**
 * Search algorithm's C++ implementation
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

#include <cmath>

#include "../Search.hpp"

using namespace cpstl;

static void custom_arguments(benchmark::internal::Benchmark* b);

static void BM_BS(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) random_array.push_back(i);
    state.ResumeTiming();
    int index = cpstl::Search<int, int>::binary_search(
        random_array, random_array.at(random_array.size() - 8));
    assert(index != -1);
  }
}

static void BM_BS_CLOSE_TO_START(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) random_array.push_back(i);
    state.ResumeTiming();
    int index = cpstl::Search<int, int>::binary_search(random_array,
                                                       random_array.at(12));
    assert(index != -1);
  }
}

static void BM_EX(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) random_array.push_back(i);
    state.ResumeTiming();
    int index = cpstl::Search<int, int>::exponential_search(
        random_array, random_array.at(random_array.size() - 8));
    // assert(index != -1);
  }
}

static void BM_EX_CLOSE_TO_START(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) random_array.push_back(i);
    state.ResumeTiming();
    int index = cpstl::Search<int, int>::exponential_search(
        random_array, random_array.at(random_array.size() - 2));
    // assert(index != -1);
  }
}

BENCHMARK(BM_BS)->Apply(custom_arguments);
BENCHMARK(BM_BS_CLOSE_TO_START)->Apply(custom_arguments);
BENCHMARK(BM_EX)->Apply(custom_arguments);
BENCHMARK(BM_EX_CLOSE_TO_START)->Apply(custom_arguments);

BENCHMARK_MAIN();

static void custom_arguments(benchmark::internal::Benchmark* b) {
  for (int i = 8; i <= 14; i++) b->Args({static_cast<long>(std::pow(2, i))});
}
