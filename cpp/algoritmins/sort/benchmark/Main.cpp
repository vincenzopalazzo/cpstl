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

#include <random>

#include "../Order.hpp"

using namespace cpstl;

Order<int> order;

static void BM_CPSTL_MERGE_SORT(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::random_device rd;
    std::mt19937 mt(rd());
    auto generator = std::uniform_int_distribution<int>(0, state.range(0));
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++)
      random_array.push_back(generator(mt));
    state.ResumeTiming();
    order.merge_sort(random_array, 0, random_array.size() - 1);
  }
}

static void BM_CPSTL_QUICK_SORT(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::random_device rd;
    std::mt19937 mt(rd());
    auto generator = std::uniform_int_distribution<int>(0, state.range(0));
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++)
      random_array.push_back(generator(mt));
    state.ResumeTiming();
    order.quick_sort(random_array, 0, random_array.size() - 1);
  }
}

static void BM_CPSTL_RANDOMIZED_QUICK_SORT(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::random_device rd;
    std::mt19937 mt(rd());
    auto generator = std::uniform_int_distribution<int>(0, state.range(0));
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++)
      random_array.push_back(generator(mt));
    state.ResumeTiming();
    order.randomize_quick_sort(random_array, 0, random_array.size() - 1);
  }
}

static void BM_CPSTL_SORTED_QUICK_SORT(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();

    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) random_array.push_back(i);
    state.ResumeTiming();
    order.quick_sort(random_array, 0, random_array.size() - 1);
  }
}

static void BM_CPSTL_SORTED_RANDOMIZED_QUICK_SORT(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++) random_array.push_back(i);
    state.ResumeTiming();
    order.randomize_quick_sort(random_array, 0, random_array.size() - 1);
  }
}

static void BM_CPST_ODD_EVEN_SORT(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::random_device rd;
    std::mt19937 mt(rd());
    auto generator = std::uniform_int_distribution<int>(0, state.range(0));
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++)
      random_array.push_back(generator(mt));
    state.ResumeTiming();
    order.odd_even_sort(random_array, 0, random_array.size() - 1);
  }
}

static void BM_STL(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::random_device rd;
    std::mt19937 mt(rd());
    auto generator = std::uniform_int_distribution<int>(0, state.range(0));
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++)
      random_array.push_back(generator(mt));
    state.ResumeTiming();
    std::sort(random_array.begin(), random_array.end());
  }
}

static void BM_SORTED_STL(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::random_device rd;
    std::mt19937 mt(rd());
    auto generator = std::uniform_int_distribution<int>(0, state.range(0));
    std::vector<int> random_array;
    random_array.reserve(state.range(0));
    for (int i = 0; i < state.range(0); i++)
      random_array.push_back(generator(mt));
    state.ResumeTiming();
    std::sort(random_array.begin(), random_array.end());
  }
}

BENCHMARK(BM_CPSTL_MERGE_SORT)->Range(1 << 10, 1 << 14);
BENCHMARK(BM_CPSTL_QUICK_SORT)->Range(1 << 10, 1 << 14);
BENCHMARK(BM_CPSTL_RANDOMIZED_QUICK_SORT)->Range(1 << 10, 1 << 14);
BENCHMARK(BM_CPSTL_SORTED_QUICK_SORT)->Range(1 << 10, 1 << 14);
BENCHMARK(BM_CPSTL_SORTED_RANDOMIZED_QUICK_SORT)->Range(1 << 10, 1 << 14);
BENCHMARK(BM_SORTED_STL)->Range(1 << 10, 1 << 14);
BENCHMARK(BM_STL)->Range(1 << 10, 1 << 14);
BENCHMARK(BM_CPST_ODD_EVEN_SORT)->Range(1 << 10, 1 << 14);

BENCHMARK_MAIN();
