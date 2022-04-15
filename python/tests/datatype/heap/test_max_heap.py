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
    inputs = [1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17]
    max_heap = MaxHeap(array=inputs)
    assert max_heap.peek() == 17
    assert max_heap.to_list() == [17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1]
    assert max_heap.is_max_heap()


def test_build_max_heap_one_optimization():
    """Build the max heap from an array"""
    inputs = [1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17]
    max_heap = MaxHeapTopDown(array=inputs)
    assert max_heap.peek() == 17
    assert max_heap.to_list() == [17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1]
    assert max_heap.is_max_heap()


def test_build_max_heap_one_optimization_insert():
    """Build the max heap from an array"""
    max_heap = MaxHeapTopDown()
    inputs = [1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17]
    for _, elem in enumerate(inputs):
        max_heap.insert(elem)
    assert max_heap.peek() == 17
    assert max_heap.to_list() == [17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1]
    assert max_heap.is_max_heap()
