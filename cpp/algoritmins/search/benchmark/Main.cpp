//
// Created by vincent on 9/18/20.
//
#include <benchmark/benchmark.h>
#include "../Search.h"

using namespace cpstl;

static void BM_BS(benchmark::State& state)
{
    for(auto _ : state) {
        state.PauseTiming();
        std::vector<int> random_array;
        random_array.reserve(state.range(0));
        for (int i = 0; i < state.range(0); i++)
            random_array.push_back(i);
        state.ResumeTiming();
        int index = binary_search(random_array, random_array.at(random_array.size() - 8), 0, random_array.size() - 1);
        assert(index != -1);
    }
}

static void BM_BS_CLOSE_TO_START(benchmark::State& state)
{
    for(auto _ : state) {
        state.PauseTiming();
        std::vector<int> random_array;
        random_array.reserve(state.range(0));
        for (int i = 0; i < state.range(0); i++)
            random_array.push_back(i);
        state.ResumeTiming();
        int index = binary_search(random_array, random_array.at(12), 0, random_array.size() - 1);
        assert(index != -1);
    }
}

static void BM_EX(benchmark::State& state)
{
    for(auto _ : state) {
        state.PauseTiming();
        std::vector<int> random_array;
        random_array.reserve(state.range(0));
        for (int i = 0; i < state.range(0); i++)
            random_array.push_back(i);
        state.ResumeTiming();
        int index = exponential_search(random_array, random_array.at(random_array.size() - 8));
        assert(index != -1);
    }
}

static void BM_EX_CLOSE_TO_START(benchmark::State& state)
{
    for(auto _ : state) {
        state.PauseTiming();
        std::vector<int> random_array;
        random_array.reserve(state.range(0));
        for (int i = 0; i < state.range(0); i++)
            random_array.push_back(i);
        state.ResumeTiming();
        int index = exponential_search(random_array, random_array.at(12));
        assert(index != -1);
    }
}

BENCHMARK(BM_BS)->Range(1<<14, 1<<18);
BENCHMARK(BM_BS_CLOSE_TO_START)->Range(1<<14, 1<<18);
BENCHMARK(BM_EX)->Range(1<<14, 1<<18);
BENCHMARK(BM_EX_CLOSE_TO_START)->Range(1<<14, 1<<18);

BENCHMARK_MAIN();

