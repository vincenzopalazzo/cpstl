//
// Created by vincent on 9/18/20.
//
#include <cmath>
#include <benchmark/benchmark.h>
#include "../Search.h"

using namespace cpstl;

static void custom_arguments(benchmark::internal::Benchmark* b);

static void BM_BS(benchmark::State& state)
{
    for(auto _ : state) {
        state.PauseTiming();
        std::vector<int> random_array;
        random_array.reserve(state.range(0));
        for (int i = 0; i < state.range(0); i++)
            random_array.push_back(i);
        state.ResumeTiming();
        int index = binary_search<int, int>(random_array, random_array.at(random_array.size() - 8), 0, random_array.size() - 1);
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
        int index = binary_search<int, int>(random_array, random_array.at(12), 0, random_array.size() - 1);
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
        int index = exponential_search<int, int>(random_array, random_array.at(random_array.size() - 8));
        //assert(index != -1);
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
        int index = exponential_search<int, int>(random_array, random_array.at(random_array.size() - 2));
        //assert(index != -1);
    }
}

BENCHMARK(BM_BS)->Apply(custom_arguments);
BENCHMARK(BM_BS_CLOSE_TO_START)->Apply(custom_arguments);
BENCHMARK(BM_EX)->Apply(custom_arguments);
BENCHMARK(BM_EX_CLOSE_TO_START)->Apply(custom_arguments);

BENCHMARK_MAIN();

static void custom_arguments(benchmark::internal::Benchmark* b)
{
    for (int i = 10; i <= 30; i++)
        b->Args({static_cast<long>(std::pow(2, i))});
}
