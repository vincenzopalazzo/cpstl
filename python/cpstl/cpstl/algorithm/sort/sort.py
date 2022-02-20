from abc import ABC, abstractmethod
from enum import Enum


class Order(Enum):
    INCREASE = 1
    DECREASE = 2


class Sort(ABC):
    """Sort Generic interface that implement all the method that
    a sort algorithm need to implement"""

    @abstractmethod
    def sort(self, sequence: list) -> list:
        """Take in input the sequence to sort and retyrn
        as result the same sequence sorted"""
        pass
