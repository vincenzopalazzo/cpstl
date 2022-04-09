"""
Similarity interface to implements similarity algorithms.
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
from abc import ABC, abstractmethod


class ISimilarity(ABC):
    """
    Each similarity algorithm needs to implement this interface
    to make the similarity concept portable between concepts.

    author: Vincenzo Palazzo https://github.com/vincenzopalazzo
    """

    @abstractmethod
    def similarity(self, set_a: list, set_b: list) -> list:
        """
        Calculate the similarity between two sets and return
        a new set with all the similar elements.
        :param set_a: first set fo elements
        :param set_b: a second set of elements
        :return: a new set with a similar element between the two sets given in input
        """
        pass
