from cpstl.datatype.min_heap import MinHeap


def test_build_min_heap():
    """Build the min heap from an array"""
    min_heap = MinHeap(array=[23, 12, 2, -1])
    assert min_heap.peek() == -1