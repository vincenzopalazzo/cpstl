from .heap import Heap


class MinHeap(Heap):
    """Min heap Python 3 implementation"""

    def cmp(self, idx_one: int, idx_two: int) -> bool:
        return self.heap[idx_one] <= self.heap[idx_two]

    def is_min_heap(self) -> bool:
        print(f"Min heap: {self}")
        return super().verify()
