"""
Min Hash algorithm implementation in pure python 3.
Copyright (C) 2021-2022 Vincenzo Palazzo vincenzopalazzodev@gmail.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
USA.
"""
from typing import Any

from .interface import ISimilarity
from .jaccard_similarity import Jaccard
from cpstl.algorithm.hash import UniversalHash
from cpstl.datatype.heap import MinHeap


class MinHash(ISimilarity):
    """
    Min Hash algorithm implementation in pure python 3.

    The algorithm is divided in different steps:
    1. Generate K random function (we use the universal hash function here);
    2. Generate the signature of each value for each hash function and take the minimum;
    3.

    author: Vincenzo Palazzo https://github.com/vincenzopalazzo
    """

    def __init__(self, hash_function_size: int, hash_function_universe: int) -> None:
        """TODO: adding the theoretical estimator for the hash_function_size"""
        self.hash_function = MinHash.__generate_hash_functions(
            hash_function_size, hash_function_universe
        )
        self.hash_to_real_value_map = dict()

    @staticmethod
    def __generate_hash_functions(size: int, universe: int) -> list:
        """Generate hash function from the input parameter

        :param size: How much hash functions need to be generated.
        :param universe: Universe of value of the hash function.
        :return list of generate hash function
        """
        hash_function = []
        for _ in range(size):
            fn = UniversalHash(size=universe)
            hash_function.append(fn)
        return hash_function

    def __add_to_map_if_missed(self, element_value: Any, element_hash: int) -> None:
        """
        Utils function that adds to a map the real value that the hash corresponds with.
        """
        if element_hash not in self.hash_to_real_value_map:
            self.hash_to_real_value_map[element_hash] = element_value

    def __take_minimum_hash_value(self, value: Any) -> int:
        """
        Use the min heap to return the minimum value of the hash functions
        :return: Minimum value between hash function result.
        """
        # due a bug inside the heap insert function
        # we need to use this work around for now
        hash_min_heap = []

        for _, fn in enumerate(self.hash_function):
            hash_elem = fn.hash_a_str(str(value))
            hash_min_heap.append(int(hash_elem))
        return MinHeap(array=hash_min_heap).peek()

    def similarity(self, set_a: list, set_b: list) -> list:
        """
        Calculate the Min Hash similarity between the two sets
        :param set_a: first set of elements
        :param set_b: second set of elements
        :return: the list of common element between the two sets
        """
        hash_set_a = set()
        hash_set_b = set()

        # feel the hash_set_a
        for _, value in enumerate(set_a):
            min_hash = self.__take_minimum_hash_value(value)
            self.__add_to_map_if_missed(element_value=value, element_hash=min_hash)
            hash_set_a.add(min_hash)

        # feel the hash_set_b
        for _, value in enumerate(set_b):
            min_hash = self.__take_minimum_hash_value(value)
            self.__add_to_map_if_missed(element_value=value, element_hash=min_hash)
            hash_set_b.add(min_hash)

        common = Jaccard().similarity(hash_set_a, hash_set_b)
        result = []
        for _, comm_elem in enumerate(common):
            if comm_elem in self.hash_to_real_value_map:
                real_value = self.hash_to_real_value_map[comm_elem]
                result.append(real_value)
        return result
