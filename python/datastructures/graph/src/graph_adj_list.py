"""
Graph data structure implementation with adjacency list in Python 3
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


class Node:
    """
    Node implementation that contains a the value of the element.
    This class contains a list of children and the value of the node.
    """

    def __init__(self, value) -> None:
        self.value = value
        self.children = []

    def add_node(self, value) -> None:
        node = Node(value)
        self.children.append(node)


class GraphList:
    """
    Class implementation of graph with adjacency list.
    This class use contains a list of node
    """

    def __init__(self, directed=False) -> None:
        self.directed = directed
        self.nodes = []

    def __dfs_helper(self, target: Node, path: list) -> None:
        pass

    def __bsf_helper(self, target: Node, path: list) -> None:
        pass

    def add_edge(self, u, v) -> None:
        pass

    def dfs(self) -> list:
        pass

    def bsf(self) -> list:
        pass
