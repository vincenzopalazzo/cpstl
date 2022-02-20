from cpstl.algorithm import HeapSort


def test_sorting_with_heap_sort():
    """Use the heap sort to sort the array"""
    sort = HeapSort()
    result = [9, 4, 5, 1, 3, 2]
    result.sort()
    assert sort.sort([3, 9, 2, 1, 4, 5]) == result
