//
// Created by vincent on 9/18/20.
//
#include <benchmark/benchmark.h>
#include "../BTree.h"

using namespace btree;

static void BM_CSTL_INSERT(benchmark::State& state)
{
    for(auto _ : state) {
        BTree<int> tree;
        for (int i = 0; i < state.range(0); i++)
            tree.insert_node(static_cast<int>(rand() % state.range(0)));
    }
}

static void BM_CSTL_DELETE(benchmark::State& state)
{
    for(auto _ : state) {
        state.PauseTiming();
        BTree<int> tree;
        for (int i = 0; i < state.range(0); i++)
            tree.insert_node(static_cast<int>(rand() % state.range(0)));
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); i++)
            tree.delete_node(tree.min());
    }
}

static void BM_STL_INSERT(benchmark::State& state)
{
    for(auto _ : state) {
        auto tree = std::set<int>();
        for (int i = 0; i < state.range(0); i++)
            tree.insert(rand() % state.range(0));
    }
}

static void BM_STL_DELETE(benchmark::State& state)
{
    for(auto _ : state) {
        state.PauseTiming();
        auto tree = std::set<int>();
        for (int i = 0; i < state.range(0); i++)
            tree.insert(rand() % state.range(0));
        state.ResumeTiming();
        for (int i = 0; i < state.range(0); i++)
            tree.erase(tree.begin());
    }
}


BENCHMARK(BM_CSTL_INSERT)->Range(1<<14, 1<<20);
BENCHMARK(BM_STL_INSERT)->Range(1<<14, 1<<20);
BENCHMARK(BM_STL_DELETE)->Range(1<<14, 1<<20);

BENCHMARK_MAIN();

