"""Genetic implementation of the Heap that give the
possibility to implement Min and Max heap.

If you want refresh your mind on how the heap is implemented, it is
possible read some well known book introduction you can read this blog post
https://www.educative.io/blog/data-structure-heaps-guide"""
from abc import ABC, abstractmethod


class Heap(ABC):
    """Generic implementation of the heap that implement
    some common function and leave to the subclass redefine
    some behaivord"""

    def __init__(self, array: list = []) -> None:
        self.heap = array
        self.from_list(array)

    def from_list(self, array: []) -> bool:
        """Build the heap from the list"""
        self.heap = array
        print(self)
        for idx in range(self.len(), -1, -1):
            self.heapify(idx)
        return self.verify()

    @staticmethod
    def parent(idx: int) -> int:
        """Calculate the parent index"""
        return idx - 1 // 2

    @staticmethod
    def left(idx: int) -> int:
        return idx * 2 + 1

    @staticmethod
    def right(idx: int) -> int:
        return (idx * 2) + 2

    def insert(self, value) -> bool:
        """Insert element inside the heap, this operation
        swap the element from the bottom to the top, and can
        be costly, a solution can be build the element from top to bottom
        it is possible proof tha the operation cost less, but for now
        in python we mantains this approach.

        Time Complexity O(log N)
        """
        self.heap.append(value)
        self.__swap_parent(len(self.heap) - 1)
        return True

    def peek(self) -> int:
        if self.len() == 0:
            raise Exception("Empty data structure")
        return self.heap[0]

    def len(self) -> int:
        return len(self.heap)

    def to_list(self) -> [int]:
        return self.heap

    def verify(self) -> bool:
        for currentIdx in range(1, len(self.heap)):
            parent_idx = Heap.parent(currentIdx)
            if not self.cmp(parent_idx, currentIdx):
                return False
        return True

    def heapify(self, node):
        """Restore the propriety inside the heap"""
        left_node = Heap.left(node)
        right_node = Heap.right(node)
        target_node = node
        if (self.len() - 1 >= left_node) and (not self.cmp(target_node, left_node)):
            target_node = left_node
        elif (self.len() - 1 >= right_node) and (not self.cmp(target_node, right_node)):
            target_node = right_node

        if target_node != node:
            self.__swap(node, target_node)
            self.heapify(target_node)

    def __swap_parent(self, node: int) -> None:
        """Take a node and check if it is possible swap it with the parent
        this mean that the heap violate the heap propriety"""
        if node is None or node < 0:
            return
        parent_idx = Heap.parent(node)
        if not self.cmp(parent_idx, node):
            self.__swap(node, parent_idx)
            self.__swap_parent(parent_idx)

    def __swap(self, idx_one: int, idx_two: int) -> None:
        """Swap the position of the two element in index {idx_two} and {idx_two}"""
        self.heap[idx_one], self.heap[idx_two] = self.heap[idx_two], self.heap[idx_one]

    def __str__(self):
        result = ""
        for _, value in enumerate(self.heap):
            result += f"{value}, "
        return result

    def __sizeof__(self):
        return self.len()

    @abstractmethod
    def cmp(self, idx_one: int, idx_two: int) -> bool:
        """Compare the two element in position {idx_one} and {idx_two}"""
        pass
