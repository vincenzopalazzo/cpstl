"""
Count Min Sketch algorithm in pure python 3.
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
from array import array
from math import pow, log
from ..hash.universal_hash import UniversalHash


def generate_n_hash_function(
    number_hashes: int, universe_hash: int = int(pow(2, 32))
) -> list:
    """
    Generate N hash functions!
    :param universe_hash: The size of the universe of the hash functions
    :param number_hashes: Number of hash functions!
    :return: return the list of hash function
    """
    hashes = []
    for _ in range(number_hashes):
        hashes.append(UniversalHash(size=universe_hash))
    return hashes


class CountMinSketch:
    """
    Count Min Sketch algorithm in pure python 3.

    The Count min sketch will divide the algorithm in different steps, like:
    - Step 1: Build a Matrix of size [C x R] with all possession sets to zero
    - Where the Colum is calculated with the formula `C = eulero_contant / approximation`
    and the row is calculated with the formula `R = ln(1 / gamma)`

    author: Vincenzo Palazzo https://github.com/vincenzopalazzo
    """

    def __init__(self, approximation: float = 0.001):
        self.size = 0
        self.matrix = []
        colum = CountMinSketch.calculate_colums(approximation)
        row = CountMinSketch.calculate_rows()
        for _ in range(row):
            table = array("l", (0 for _ in range(colum)))
            self.matrix.append(table)

        # generate R hash functions, with a universe that is `h -> [c]`
        self.hash_functions = generate_n_hash_function(
            number_hashes=row, universe_hash=colum
        )

    @staticmethod
    def calculate_colums(approximation: float) -> int:
        """
        Calculate the colums size from an approximation number
        :param approximation:
        :return: Size of the colums calculate with the formula `C = eulero_contant / approximation`
        """
        eulero_constant = 2.71828
        return int(eulero_constant / approximation)

    @staticmethod
    def calculate_rows() -> int:
        """"""
        return int(log((1 / (1 / 3)), 2))

    def __compute_hashes(self, val):
        if not isinstance(val, int):
            raise Exception(
                "Value not an instance of int, other type are not supported by the Universal Hash function!"
            )
        for idx in range(len(self.hash_functions)):
            yield self.hash_functions[idx].hash(val)

    def increment(self, value, increment: int = 1) -> None:
        """Apply an increment to the value"""
        self.size += increment
        for table, i in zip(self.matrix, self.__compute_hashes(value)):
            table[i] += increment

    def query(self, value) -> int:
        """Query the data structure and return the estimation frequency of the value"""
        print(self.matrix)
        return min(
            table[i] for table, i in zip(self.matrix, self.__compute_hashes(value))
        )

    def __getitem__(self, item):
        return self.query(item)

    def __len__(self):
        return self.size
