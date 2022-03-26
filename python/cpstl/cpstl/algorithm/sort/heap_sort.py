from .sort import Sort, Order
from cpstl.datatype.heap import MaxHeap, MinHeap


class HeapSort(Sort):
    """Heap sort algorithm pure Python 3 implementation"""

    def sort(self, sequence: list, order=Order.INCREASE) -> list:
        heap = self.build_heap(sequence, order)
        print("---- start ------")
        offset = 1
        for idx in reversed(range(1, heap.len())):
            print(f"idx {idx}")
            heap.swap(0, idx)
            heap.heapify(0, size_offset=offset)
            offset += 1
        return heap.to_list()

    def build_heap(self, sequence: list, order: Order = Order.INCREASE):
        """"""
        if order == Order.INCREASE:
            return MaxHeap(sequence)
        return MinHeap(sequence)
