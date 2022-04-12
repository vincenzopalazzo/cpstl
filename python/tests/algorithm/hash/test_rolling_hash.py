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

from cpstl.algorithm.hash import RollingHash


def test_same_hash_with_same_function() -> None:
    """Check if we repeater the same calculation each time we have the same result"""
    hash = RollingHash()
    str_to_hash = "need to be the same hash each time"
    first_hash = hash.hash_str(str_to_hash)
    for _ in range(0, 1000):
        assert first_hash == hash.hash_str(str_to_hash)
