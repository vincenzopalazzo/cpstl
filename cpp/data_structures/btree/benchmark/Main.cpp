//
// Created by vincent on 9/18/20.
//
#include <benchmark/benchmark.h>
#include "../BTree.h"

using namespace btree;

static void BM_CSTL(benchmark::State& state)
{
    for(auto _ : state) {
        auto *root = new Node<int>;
        for (int i = 0; i < state.range(0); i++)
            insert_node(root, static_cast<int>(rand() % state.range(0)));
    }
}

static void BM_STL(benchmark::State& state)
{
    for(auto _ : state) {
        auto tree = std::set<int>();
        for (int i = 0; i < state.range(0); i++)
            tree.insert(rand() % state.range(0));
    }
}


BENCHMARK(BM_CSTL)->Range(1<<14, 1<<20);
BENCHMARK(BM_STL)->Range(1<<14, 1<<20);

BENCHMARK_MAIN();

