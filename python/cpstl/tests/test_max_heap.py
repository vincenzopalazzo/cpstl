from cpstl.datatype import MaxHeap


def test_build_max_heap():
    """Build the min heap from an array"""
    max_heap = MaxHeap(array=[3, 9, 2, 1, 4, 5])
    assert max_heap.to_list() == [9, 4, 5, 1, 3, 2]
    assert max_heap.peek() == 9
    assert max_heap.is_max_heap()
