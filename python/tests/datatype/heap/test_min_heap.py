import logging
import heapq

from cpstl.datatype.heap import MinHeap, MinHeapTopDown

logger = logging.Logger(__name__)


def test_build_min_heap():
    """Build the min heap from an array"""
    min_heap = MinHeap(array=[3, 9, 2, 1, 4, 5])
    assert min_heap.to_list() == [1, 3, 2, 9, 4, 5]
    assert min_heap.peek() == 1
    assert min_heap.is_min_heap()


def test_build_min_heap_one_insert():
    """Build the max heap from an array"""
    min_heap = MinHeap()
    inputs = [3, 9, 2, 1, 4, 5]
    for elem in inputs:
        min_heap.insert(elem)
    heapq.heapify(inputs)
    assert min_heap.to_list() == inputs
    assert min_heap.peek() == 1
    assert min_heap.is_min_heap()


def test_build_min_heap_one_optimization():
    """Build the max heap from an array"""
    inputs = [3, 9, 2, 1, 4, 5]
    min_heap = MinHeapTopDown(array=inputs)
    heapq.heapify(inputs)
    assert min_heap.to_list() == inputs
    assert min_heap.peek() == 1
    assert min_heap.is_min_heap()


def test_build_min_heap_one_optimization_insert():
    """Build the max heap from an array"""
    min_heap = MinHeapTopDown()
    inputs = [3, 9, 2, 1, 4, 5]
    for _, elem in enumerate(inputs):
        min_heap.insert(elem)
    heapq.heapify(inputs)
    assert min_heap.to_list() == inputs
    assert min_heap.peek() == 1
    assert min_heap.is_min_heap()
