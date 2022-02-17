"""Genetic implementation of the Heap that give the
possibility to implement Min and Max heap"""
from abc import ABC, abstractmethod


class HeapNode:
    """Heap Node implementation that give the possibility
    to abstract the wal strategy"""

    def __init__(self, value, idx: int) -> None:
        self.value = value
        self.idx = idx

    def __gt__(self, other):
        return self.value > other.value

    def __lt__(self, other):
        return self.value < other.value

    def __eq__(self, other):
        return self.value == other.value

    def left(self) -> int:
        """Return the index of the left child"""
        return (self.idx * 2) + 1

    def right(self) -> int:
        """Return the index of the right child"""
        return (self.idx * 2) + 2

    def parent(self) -> int:
        return (self.idx + 1) // 2


class Heap(ABC):
    """Generic implementation of the heap that implement
    some common function and leave to the subclass redefine
    some behaivord"""

    def __init__(self, array: list = []) -> None:
        self.heap = []
        self.build(array)

    def build(self, array: []) -> bool:
        for elem in array:
            self.insert(elem)
        return True

    def insert(self, value) -> bool:
        node = HeapNode(value, len(self.heap))
        self.heap.append(node)
        self.__sift_down(0, self.len() - 1)
        return True

    def peek(self) -> int:
        if self.len() == 0:
            raise Exception("Empty data structure")
        return self.heap[0].value

    def __at(self, idx: int) -> HeapNode:
        return self.heap[idx]

    def len(self) -> int:
        return len(self.heap)

    def __sift_up(self, current_idx: int):
        """Move the element at {currentIdx} to the top of the Min heap"""
        current_node = self.__at(current_idx)
        parent_idx = current_node.parent()
        while parent_idx > 0 and self.cmp(parent_idx, current_idx):
            self.swap(current_idx, parent_idx)
            current_idx = parent_idx
            parent_idx = self.__at(current_idx).parent()

    def __sift_down(self, current_idx: int, end_idx: int):
        """Move the element at {current_idx} to the {end_idx} position of the Min Heap"""
        current_node = self.__at(current_idx)
        while current_node.left() <= end_idx:
            left_idx = current_node.left()
            # Improove the readibility of the code, and
            # avoid that variable jump out in some strange workflow
            right_idx = -1
            swap_idx = -1
            if current_node.right() <= end_idx:
                right_idx = current_node.right()
            if right_idx != -1 and self.cmp(right_idx, current_idx):
                swap_idx = right_idx
            else:
                swap_idx = left_idx
            if self.cmp(swap_idx, current_idx):
                self.swap(swap_idx, current_idx)
                current_node = self.__at(swap_idx)
            else:
                return

    def swap(self, idx_one: int, idx_two: int) -> None:
        """Swap the position of the two element in index {idx_two} and {idx_two}"""
        one_node = self.heap[idx_one]
        two_node = self.heap[idx_two]
        two_node.idx = idx_one
        one_node.idx = idx_two
        self.heap[idx_one] = two_node
        self.heap[idx_two] = one_node

    @abstractmethod
    def cmp(self, idx_one: int, idx_two: int) -> bool:
        """Compare the two element in position {idx_one} and {idx_two}"""
        pass
