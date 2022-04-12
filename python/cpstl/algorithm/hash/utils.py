"""
hash package written in pure python 3.
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
from math import sqrt


class Utils:
    @staticmethod
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

    @staticmethod
    def convert_str_to_byte(input_str: str) -> str:
        """Convert the input string into the sequence of bytes into a string form"""
        return "".join(format(ord(i), "08b") for i in input_str)
