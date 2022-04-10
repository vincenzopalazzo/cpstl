from cpstl.datatype.heap import Heap, HeapTopDown


class MaxHeap(Heap):
    """Max Heap Python implementation"""

    def cmp(self, idx_one: int, idx_two: int) -> bool:
        return self.heap[idx_one] >= self.heap[idx_two]

    def is_max_heap(self) -> bool:
        print(f"Max heap {self}")
        return self.verify()


class MaxHeapTopDown(HeapTopDown):
    """Use optimization of heap to improve the insert time from O(N log N) to O(N)"""

    def cmp(self, start_idx: int, with_idx: int) -> bool:
        start_node = self.heap[start_idx]
        with_node = self.heap[with_idx]
        return start_node >= with_node

    def is_max_heap(self) -> bool:
        print(f"Max heap {self}")
        return self.verify()
