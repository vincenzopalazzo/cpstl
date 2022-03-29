"""
Universal Hashing algorithm in pure python 3.
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
from math import sqrt


def generate_random_prime(target_number: int) -> int:
    """
    Trivial function to generate a random prime number,
    from a target number.
    :return: The prime number generated.
    """
    for number in range(target_number + 1, (2 * target_number) + 1):
        is_prime = True
        for prime in range(3, int(sqrt(number) - 1), -1):
            if prime % 2 == 0:
                is_prime = False
                break
        if is_prime:
            return number
    raise Exception(f"Prime number not found with target number {target_number}!")


class UniversalHash:
    """
    Universal Hashing algorithm in pure python 3.

    author: Vincenzo Palazzo https://github.com/vincenzopalazzo
    """

    def __init__(self, size: int = -1):
        """Init the Universal Hash with a default size of 10 (take a random number, no motivation here)"""
        self.value_a = -1
        self.value_b = -1
        self.size = size
        self.prime_number = generate_random_prime(size)
        self.random_choice()

    def random_choice(self) -> None:
        """Make a random choice"""
        self.value_a = random.randint(1, self.prime_number - 1)
        self.value_b = random.randint(0, self.prime_number - 1)

    def hash(self, value_to_hash: int) -> int:
        """Calculate the universal hash value of the value"""
        assert self.value_a >= 0 and self.value_b >= 0, (
            "Random A and B value are not initialized, this should " "never happens "
        )
        return (
            (self.value_a * value_to_hash * self.value_b) % self.prime_number
        ) % self.size
