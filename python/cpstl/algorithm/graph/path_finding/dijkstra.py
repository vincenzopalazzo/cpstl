"""
Dijkstra Path finding algorithm implemented in pure Python 3
Copyright (C) 2021 Vincenzo Palazzo vincenzopalazzodev@gmail.com

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
from typing import Sequence, Callable

from cpstl.datatype.graph import Node


def dijkstra(source: Node, destination: Node, get_weight_callback: Callable[[Node], float] = None) -> Sequence[Node]:
    """Apply Dijkstra algorithm on the graph to find the best.

    Reference implementation: https://stackabuse.com/dijkstras-algorithm-in-python

    author: Vincenzo Palazzo https://github.com/vincenzopalazzo

    :param source: The source node where the search of the path will start
    :param destination: The destination node where we would like to arrive
    :param get_weight_callback: callback to get the weight from the node. The caller needs to define when propriety is not defined.
    :return the path if exist
    """
    return []
