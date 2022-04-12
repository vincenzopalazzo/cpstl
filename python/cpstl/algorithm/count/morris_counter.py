"""
Morris Counter algorithm in pure python 3.
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
import math
import random
import logging


def simulate_next_value(next_value: int) -> float:
    return (math.e ** (math.log(2) * next_value)) - 1


class MorrisCounter:
    """
    Morris Counter algorithm in pure python 3.

    author: Vincenzo Palazzo https://github.com/vincenzopalazzo
    """

    def __init__(self) -> None:
        self.__counter = 0

    def increment(self):
        """Increment the counter!"""
        next_value = simulate_next_value(self.__counter + 1)
        counter = 1 / (next_value - self.get_value())
        rand_num = random.uniform(0, 1)
        if rand_num < counter:
            self.__counter += 1

    def get_value(self) -> int:
        return int(simulate_next_value(self.__counter))
