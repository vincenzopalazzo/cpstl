//
// Created by vincent on 10/17/20.
//
#include <cassert>
#include "FenwickTree.h"

template<class T>
void cpstl::BTreeIndex<T>::update(const T &value, int at)
{
    assert(at > 0 && "The position inside the array should be greater than 0");
    while (at < structure.size()) {
        structure[at] += value;
        at += indexing(at);
    }
}

template<class T>
T cpstl::BTreeIndex<T>::sum(int begin, int end)
{
    assert(begin >= 0 && end >= 0);
    T sum = 0;
    int at = end;
    while (at > begin) {
        sum += structure[at];
        at &= at - 1;
        //at -= indexing(at);
    }
    return sum;
}

template<class T>
T cpstl::BTreeIndex<T>::sum(int end)
{
    assert(end >= 0);
    T sum = 0;
    int at = end;
    while (at > 0) {
        sum += structure[at];
        at &= at -1;
        //at -= indexing(at);
    }
    return sum;
}

template<class T>
int cpstl::BTreeIndex<T>::min(T const value) {
    return -1;
}

template<class T>
int cpstl::BTreeIndex<T>::max(T const value) {
    return -1;
}

template<class T>
int cpstl::BTreeIndex<T>::indexing(int index)
{
    return index& -index;
}

template<class T>
cpstl::BTreeIndex<T>::BTreeIndex(int size)
{
    structure = std::vector<T>(size + 1);
}

template<class T>
cpstl::BTreeIndex<T>::BTreeIndex(const std::vector<T> &structure)
{
    this->structure.reserve(structure.size() + 1);
    this->structure[0] = 0;
    for (int i = 0; i < structure.size(); i++) {
        this->structure[i + 1] = structure[i];
    }

    int at = 1;
    while (at < this->structure.size()) {
        int at_tree = indexing(at);
        this->structure[at_tree] += this->structure[at];
        at += indexing(at);
    }
}

template class cpstl::BTreeIndex<int>;