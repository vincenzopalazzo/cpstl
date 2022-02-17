from .heap import Heap


class MinHeap(Heap):
    """Min heap Python 2 implementation"""

    def cmp(self, idx_one: int, idx_two: int) -> bool:
        return self.heap[idx_one] < self.heap[idx_two]
