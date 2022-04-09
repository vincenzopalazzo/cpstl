"""
Flajolet–Martin (FM) Sketch algorithm in pure python 3.
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
from ..hash.universal_hash import UniversalHash


class FMSketch(object):
    """
    Flajolet–Martin (FM) Sketch algorithm in pure python 3.

    The problem that we are going to solve with this algorithm is the
    following on:

    Let S be a multi-set of N integers, namely, two elements of S may be identical. Each integer is in
    the range of [0, D] where D is some polynomial of N. The distinct element counting problem is to
    find out exactly how many distinct elements there are in S. We will use F to denote the answer.
    For example, given S = {1, 5, 10, 5, 15, 1}, F = 4.

    Clearly, using O(N) words of space, the problem can be solved easily in O(N log N) time by
    sorting, or O(N) expected time with hashing. However, in many applications, the amount of space
    at our disposal can be much smaller.

    The following algorithm allowed us to count unique elements in only O(log N)
    bits. Hence, our goal is to obtain an approximate answer F˜ whose accuracy has a probabilistic
    guarantee.

    Pseudo Code-Stepwise Solution:

        1. Selecting a hash function h so each element in the set is mapped to a string to at least log2n bits;
        2. For each element x, r(x)= length of trailing zeroes in h(x);
        3. R= max(r(x));

    Now it is possible to estimate the distinct elements by the following formula
    Distinct elements= 2^R

    author: Vincenzo Palazzo https://github.com/vincenzopalazzo
    """

    @staticmethod
    def count_distinct(input_list: list, bits: int = 64) -> int:
        """
        Return the number of distinct elements in the input list.
        :return: The FM estimation of distinct elements in the list of elements.
        """
        max_zeros_sum = 0
        # number of univers! that in this case is the number of bits
        universal_hashing = UniversalHash(size=pow(2, bits))
        for index in range(len(input_list)):
            # The hash function returns an integer that is a binary presentation
            # of the hash value returned.
            hash_val = bin(universal_hashing.hash(input_list[index]))[2:]
            zeros_sum = 0
            for val in range(len(hash_val) - 1, 0, -1):
                if hash_val[val] == "0":
                    zeros_sum += 1
                else:
                    break
            if zeros_sum > max_zeros_sum:
                max_zeros_sum = zeros_sum
        return pow(2, max_zeros_sum)
