import heapq
from cpstl.datatype.heap import MaxHeap, MaxHeapTopDown


def test_build_max_heap_one():
    """Build the max heap from an array"""
    max_heap = MaxHeap(array=[3, 9, 2, 1, 4, 5])
    assert max_heap.to_list() == [9, 4, 5, 1, 3, 2]
    assert max_heap.peek() == 9
    assert max_heap.is_max_heap()


def test_build_max_heap_one_insert():
    """Build the max heap from an array"""
    max_heap = MaxHeap()
    for _, elem in enumerate([3, 9, 2, 1, 4, 5]):
        max_heap.insert(elem)
    assert max_heap.to_list() == [9, 4, 5, 1, 3, 2]
    assert max_heap.peek() == 9
    assert max_heap.is_max_heap()


def test_build_max_heap_two():
    """Build the max heap from an array"""
    input = [48, 12, 24, 7, 8, -5, 24, 391, 24, 56, 2, 6, 8, 41]
    max_heap = MaxHeap(array=input)
    assert max_heap.peek() == 391
    assert max_heap.is_max_heap()
    heapq.heapify(input)
    assert max_heap.to_list() == input


def test_build_max_heap_one_optimization():
    """Build the max heap from an array"""
    input = [48, 12, 24, 7, 8, -5, 24, 391, 24, 56, 2, 6, 8, 41]
    max_heap = MaxHeapTopDown(array=input)
    assert max_heap.peek() == 391
    assert max_heap.is_max_heap()
    heapq.heapify(input)
    assert max_heap.to_list() == input


def test_build_max_heap_one_optimization_insert():
    """Build the max heap from an array"""
    max_heap = MaxHeapTopDown()
    for _, elem in enumerate([3, 9, 2, 1, 4, 5]):
        max_heap.insert(elem)
    assert max_heap.to_list() == [9, 4, 5, 1, 3, 2]
    assert max_heap.peek() == 9
    assert max_heap.is_max_heap()
