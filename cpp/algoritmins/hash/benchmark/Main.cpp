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

#include "../PerfectHash.hpp"

using namespace cpstl;


static void BM_CPP_PERFECT_HASHING(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> inputs;
    for (int i = 0; i < state.range(0); i++) {
      inputs.push_back(i);
    }
    state.ResumeTiming();
    cpstl::PerfectHash<int> perfect_map(inputs.size());
    perfect_map.insert_list(inputs);
  }
}

BENCHMARK(BM_CPP_PERFECT_HASHING)->DenseRange(20, 1024, 128);

BENCHMARK_MAIN();
