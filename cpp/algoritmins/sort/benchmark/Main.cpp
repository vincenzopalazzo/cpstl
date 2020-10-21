//
// Created by vincent on 9/18/20.
//
#include <benchmark/benchmark.h>
#include "../Order.h"

using namespace cpstl;

static void BM_CPSTL_MERGE_SORT(benchmark::State& state)
{
    for(auto _ : state) {
        state.PauseTiming();
        std::vector<int> random_array;
        random_array.reserve(state.range(0));
        for (int i = 0; i < state.range(0); i++)
            random_array.push_back(i);
        state.ResumeTiming();
        merge_sort(random_array, 0, random_array.size() - 1);
    }
}

static void BM_STL(benchmark::State& state)
{
    for(auto _ : state) {
        state.PauseTiming();
        std::vector<int> random_array;
        random_array.reserve(state.range(0));
        for (int i = 0; i < state.range(0); i++)
            random_array.push_back(i);
        state.ResumeTiming();
        std::sort(random_array.begin(), random_array.end());
    }
}

BENCHMARK(BM_CPSTL_MERGE_SORT)->Range(1<<14, 1<<18);
BENCHMARK(BM_STL)->Range(1<<14, 1<<18);

BENCHMARK_MAIN();

