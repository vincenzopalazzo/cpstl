"""
Jaccard Sim algorithm implementation in pure python 3.
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
from .interface import ISimilarity


class Jaccard(ISimilarity):
    """
    Jaccard Sim algorithm implementation in pure python 3.

    author: Vincenzo Palazzo https://github.com/vincenzopalazzo
    """

    @staticmethod
    def __intersection_set(set_a: set, set_b: set) -> set:
        """Make the intersection of the two lists"""
        return set(set_a).intersection(set_b)

    @staticmethod
    def __union_set(set_a: set, set_b: set) -> set:
        """Make the union of the two list"""
        return set(set_a).union(set_b)

    def similarity(self, set_a: set, set_b: set) -> set:
        intersection = Jaccard.__intersection_set(set_a, set_b)
        union = Jaccard.__union_set(set_a, set_b)
        result = set()
        for _, elem in enumerate(union):
            if elem in intersection:
                result.add(elem)
        return result
