/**
 * Bloom Filter with Universal Hashing C++ implementation
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

#include "../BloomFilter.hpp"

std::random_device rd;
std::mt19937_64 mt(rd());

static void CustomArguments(benchmark::internal::Benchmark* b);

static void BM_BLOOM_FILTER_REPORT(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    auto inputGenerator =
        std::uniform_int_distribution<long>(0, state.range(0));
    auto notInsideGen = std::uniform_int_distribution<long>(state.range(0) + 1,
                                                            2 * state.range(0));
    std::vector<long> inputs;
    std::vector<long> notInside;

    for (std::size_t i = 0; i < state.range(0); i++) {
      inputs.push_back(inputGenerator(mt));
      notInside.push_back(notInsideGen(mt));
    }
    state.ResumeTiming();
    cpstl::BloomFilter<long> bloomFilter(state.range(0), state.range(1));
    for (auto elem : inputs) bloomFilter.insert(elem);
    auto countFalsePositive = 0;
    for (auto elem : notInside) {
      auto result = bloomFilter.contains(elem);
      if (result == true) countFalsePositive++;
    }
    state.counters["FalsePositive"] = countFalsePositive;
  }
}

BENCHMARK(BM_BLOOM_FILTER_REPORT)->Apply(CustomArguments)->Complexity();
BENCHMARK_MAIN();

static void CustomArguments(benchmark::internal::Benchmark* b) {
  long j = 1;
  for (int i = 4; i <= 21; i++) {
    // in the formula the probability to have an false positive is (log2)^(m/n)
    // where m is the size of the filter and n is the size of the inputs array
    // and in the following args the value are
    // <n, factor to calculate the size of the filter>
    b->Args({static_cast<long>(std::pow(2, i)), static_cast<long>(j)});
    j++;
  }
}
