"""
Count Min Sketch algorithm in pure python 3.
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
from cpstl.algorithm.sketch.count_min_sketch import CountMinSketch


def test_count_min_sketch():
    """Simple test of usage of Count Min Sketch"""
    sketch = CountMinSketch()
    sketch.increment(12)
    sketch.increment(10)
    sketch.increment(1, increment=123)
    assert sketch[12] == 1
    assert sketch[10] == 1
    assert sketch[1] == 123
    assert sketch[98] == 0
