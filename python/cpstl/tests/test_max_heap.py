from cpstl.datatype import MaxHeap


def test_build_max_heap():
    """Build the min heap from an array"""
    min_heap = MaxHeap(array=[23, 12, 2, -1])
    assert min_heap.peek() == 23