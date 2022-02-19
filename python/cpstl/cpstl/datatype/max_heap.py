from .heap import Heap


class MaxHeap(Heap):
    """Max Heap Python implementation"""

    def cmp(self, idx_one: int, idx_two: int) -> bool:
        return self.heap[idx_one] >= self.heap[idx_two]

    def is_max_heap(self) -> bool:
        print(f"Max heap {self}")
        return self.verify()
