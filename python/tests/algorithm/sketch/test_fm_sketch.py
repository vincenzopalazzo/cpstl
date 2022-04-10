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
from cpstl.algorithm.sketch.flajolet_martin import FMSketch


def test_fm_sketch():
    """FM Sketch algorithm"""
    stream = [1, 2, 3, 4, 5, 6, 4, 2, 5, 9, 1, 6, 3, 7, 1, 2, 2, 4, 2, 1]
    found = False
    # The hash function can be badly defined!
    # so we iterate and check sometimes
    for _ in range(10):
        counter = FMSketch.count_distinct(stream)
        if counter == len(set(stream)):
            found = True
    assert found
