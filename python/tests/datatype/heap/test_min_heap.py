import logging

from cpstl.datatype.heap import MinHeap, MinHeapTopDown

logger = logging.Logger(__name__)


def test_build_min_heap():
    """Build the min heap from an array"""
    min_heap = MinHeap(array=[3, 9, 2, 1, 4, 5])
    assert min_heap.to_list() == [1, 3, 2, 9, 4, 5]
    assert min_heap.peek() == 1
    assert min_heap.is_min_heap()


def test_build_max_heap_one_insert():
    """Build the max heap from an array"""
    max_heap = MinHeap()
    for _, elem in enumerate([3, 9, 2, 1, 4, 5]):
        max_heap.insert(elem)
    assert max_heap.to_list() == [1, 3, 2, 9, 4, 5]
    assert max_heap.peek() == 1
    assert max_heap.is_min_heap()


def test_build_min_heap_one_optimization():
    """Build the max heap from an array"""
    input = [3, 9, 2, 1, 4, 5]
    min_heap = MinHeapTopDown(array=input)
    assert min_heap.to_list() == [1, 3, 2, 9, 4, 5]
    assert min_heap.peek() == 1
    assert min_heap.is_min_heap()
