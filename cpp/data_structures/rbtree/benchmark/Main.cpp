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
#include <cmath>

#include <benchmark/benchmark.h>
#include "../RBTree.hpp"

using namespace cpstl;

static void BM_RBTREE_INSERT(benchmark::State& state) {
  RBTree<long> tree;
  for (auto _ : state) {
    for (int i = 3; i < state.range(0); i++) {
      tree.insert(i);
    }
  }
}

static void BM_CPP_STL_SET(benchmark::State& state) {
  std::set<int> tree;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); i++) {
      tree.insert(i);
    }
  }
}

BENCHMARK(BM_RBTREE_INSERT)->DenseRange(20, 1024, 128);
BENCHMARK(BM_CPP_STL_SET)->DenseRange(20, 1024, 128);

BENCHMARK_MAIN();
