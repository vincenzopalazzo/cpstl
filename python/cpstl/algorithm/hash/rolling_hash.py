"""
Rolling Hash algorithm in pure python 3.
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
import random
from .utils import Utils


class RollingHash:
    """
    Karp Rabin Algorithm implementation in pure python 3
    with reference implementation of the C++ implementation.

    Reference implementation: https://github.com/vincenzopalazzo/cpstl/blob/master/cpp/algoritmins/karp_rabin_fingerprint/KarpRabinHash.hpp

    author: Vincenzo Palazzo https://github.com/vincenzopalazzo
    """

    def __init__(self) -> None:
        # FIXME: remove this static array, and add an
        # and algorithm to choose the prime number.
        self.prime_numbers = [
            62563,
            62581,
            62591,
            62597,
            62603,
            62617,
            62627,
            62633,
            62639,
            62653,
        ]
        self.prime_number = random.choice(self.prime_numbers)

    def hash_str(self, str_to_hash: str) -> int:
        """Compute the hash of the input string"""
        return self.hash_from_byte(Utils.convert_str_to_byte(str_to_hash))

    def hash_from_byte(self, sequence_of_byte: str) -> int:
        """Compute the hash of the sequence of byte given in input"""
        fingerprint = 0
        for char in sequence_of_byte:
            bit = int(char)
            # x' = ((x « 1) + bit[i]) % p
            fingerprint = ((fingerprint * 2) + bit) % self.prime_number
        return fingerprint
