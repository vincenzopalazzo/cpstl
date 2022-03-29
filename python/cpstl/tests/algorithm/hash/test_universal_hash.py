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
from cpstl.algorithm.hash import UniversalHash


def test_universal_hash_function_one():
    """First test of Universal Hash function base on the following
    test case https://github.com/vincenzopalazzo/cpstl/blob/master/cpp/algoritmins/hash/test/Main.cpp#L40"""
    inputs = [11, 25, 36, 41, 57, 66, 73, 89, 95]
    universal_hash = UniversalHash(size=len(inputs))
    map_elem = {}

    for elem in inputs:
        hash_elem = universal_hash.hash(elem)
        if hash_elem in map_elem:
            list_elem = map_elem[hash_elem]
            list_elem.append(hash_elem)
        else:
            map_elem[hash_elem] = [hash_elem]

    collision = False
    for elem in inputs:
        hash_elem = universal_hash.hash(elem)
        list_hash = map_elem[hash_elem]
        if len(list_hash) > 1:
            collision = True

    assert (
        collision
    ), f"Collision detected in the input {inputs} and map of hashes {map_elem}"
