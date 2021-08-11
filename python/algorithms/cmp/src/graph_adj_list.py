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
from queue import Queue


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
        path.append(target.value)
        for node in target.children:
            self.__dfs_helper(node, path)

    def __bsf_helper(self, target: Node, path: list) -> None:
        to_visit = Queue()
        to_visit.put(target)
        while not to_visit.empty():
            node = to_visit.get()
            path.append(node.value)
            for child in node.children:
                to_visit.put(child)

    def __find_node(self, node: Node, value) -> Node:
        """
        Find the node with the value in the node
        if it exist return the node, otherwise return None
        """
        if node.value == value:
            return node
        for child in node.children:
            found = self.__find_node(child, value)
            if found is not None:
                return found
        return None

    def __find_node_add(self, node: Node, value, to_add) -> bool:
        """
        Find the node with the value in the node
        if it exist return the node, otherwise return None
        """
        if node.value == value:
            node.add_node(to_add)
            return True
        for child in node.children:
            found = self.__find_node(child, value)
            if found is True:
                return True
        return False

    def add_edge(self, u, v) -> None:
        """
        Adding a edge to graph, if directed is true
        add the edge from u -> v, otherwise adding a
        edge u -> v and v -> u.
        """
        if self.directed:
            if len(self.nodes) != 0:
                for node in self.nodes:
                    found = self.__find_node_add(node, u, v)
                    if found is True:
                        return
            node = Node(u)
            node.add_node(v)
            self.nodes.append(node)
        else:
            raise RuntimeError("unsupported undirected graph")

    def dfs(self) -> list:
        paths = []
        for node in self.nodes:
            path = []
            self.__dfs_helper(node, path)
            paths.append(path)
        return paths

    def bfs(self) -> list:
        paths = []
        for node in self.nodes:
            path = []
            self.__bsf_helper(node, path)
            print(path)
            paths.append(path)
        return paths

    def size(self) -> int:
        uniques = set()
        for node in self.nodes:
            uniques.add(node.value)
            for child in node.children:
                uniques.add(child.value)
        return len(uniques)

    def cliques(self, min_size: int, max_size: int) -> list:
        """
        Find the cliques in the graph, and return a list of nodes.
        min_size: Minimum size of a clique
        max_size: Max size of a clique
        """
        print("Not implemented yet")
        return []

