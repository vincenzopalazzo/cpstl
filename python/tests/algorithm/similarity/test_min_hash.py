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
from cpstl.algorithm.similarity import MinHash


def test_min_hash() -> None:
    """Simple test of the jaccard similarity"""
    set_a = ["vincenzo", "alibaba", "kotlin", "dart"]
    set_b = ["v", "elefante", "dart", "rust", "koltin"]

    similarity = MinHash(
        hash_function_size=10, hash_function_universe=int(pow(2, 32))
    ).similarity(set_a, set_b)
    similarity.sort()
    real = ["kotlin", "dart"]
    real.sort()
    assert similarity == real
