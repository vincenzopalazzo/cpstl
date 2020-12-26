//
// Created by vincent on 9/14/20.
//
#ifndef SPYCBLOCK_SOLTEST_H
#define SPYCBLOCK_SOLTEST_H
#include <cstdlib>
#include <string>
#include <vector>
#include "SegmentTree.h"
#include "../LazySegmentTree.h"

template <typename T>
struct Query {
    bool update;
    T start;
    T end;
    Query(bool type, T start, T anEnd) : update(type), start(start), end(anEnd) {}
};

template <typename T>
std::vector<T> range_minimum_query_lazy_segment_tree(cpstl::LazySegmentTree<T> &segmentTree, std::vector<Query<T>> &queries)
{
    std::vector<T> results;
    results.reserve(queries.size());
    for (auto &query : queries) {
        if (query.update) {
            segmentTree.update(query.start - 1, query.end);
            continue;
        }
        auto res = segmentTree.range_query(query.start - 1, query.end - 1);
        results.push_back(segmentTree.value_at(res));
    }
    return results;
}

template <typename T>
std::vector<T> range_minimum_query_segment_tree(cpstl::SegmentTree<T> &segmentTree, std::vector<Query<T>> &queries)
{
    std::vector<T> results;
    results.reserve(queries.size());
    for (auto &query : queries) {
        if (query.update) {
            segmentTree.update(query.start - 1, query.end);
            continue;
        }
        auto res = segmentTree.range_query(query.start - 1, query.end - 1);
        results.push_back(segmentTree.value_at(res));
    }
    return results;
}

#endif //SPYCBLOCK_SOLTEST_H
