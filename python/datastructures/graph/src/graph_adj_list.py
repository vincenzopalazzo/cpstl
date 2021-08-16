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
from itertools import product


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

    def __str__(self):
        if len(self.children) == 0:
            return "{}".format(self.value)
        return "{}: with {} edges".format(self.value, len(self.children))


class Edge:
    """
    Edge implementation that constains two node, in the literature it is known as
    (u, v).
    """

    def __init__(self, u: Node, v: Node):
        self.u = u
        self.v = v

    def __str__(self):
        return "({}, {})".format(self.u.value, self.v.value)


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

    def __find_node_add(self, node: Node, value, to_add, directed=True) -> bool:
        """
        Find the node with the value in the node
        if it exist return the node, otherwise return None
        """
        if node.value == value:
            node.add_node(to_add)
            if directed is False:
                node.children[len(node.children) - 1].add_node(node.value)
            return True
        for child in node.children:
            found = self.__find_node(child, value)
            if found is True:
                return True
        return False

    def __cartesian_product(self) -> list:
        edges = list()
        for node in self.nodes:
            for child in node.children:
                edges.append(Edge(node, child))
        return edges

    def add_edge(self, u, v) -> None:
        """
        Adding a edge to graph, if directed is true
        add the edge from u -> v, otherwise adding a
        edge u -> v and v -> u.
        """
        if self.directed:
            if len(self.nodes) != 0:
                for node in self.nodes:
                    found = self.__find_node_add(node, u, v, self.directed)
                    if found is True:
                        return
            node = Node(u)
            node.add_node(v)
            self.nodes.append(node)
        else:
            if len(self.nodes) != 0:
                for node in self.nodes:
                    found = self.__find_node_add(node, u, v, self.directed)
                    if found is True:
                        return
            node_u = Node(u)
            node_u.add_node(v)

            node_v = Node(v)
            node_v.add_node(u)

            self.nodes.append(node_u)
            self.nodes.append(node_v)

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

    def edges(self) -> list:
        edges = list()
        for node in self.nodes:
            for child in node.children:
                edges.append((node, child))
        return edges

    def to_undirected(self):
        """
        Convert a directed graph to undirected graph
        """
        if self.directed is False:
            raise ValueError("The graph is already undirected")
        graph = GraphList(directed=False)
        for node in self.nodes:
            for child in node.children:
                graph.add_edge(node.value, child.value)
        return graph

    def cliques(self, min_size: int = 3, max_size: int = 3) -> list:
        """
        Find the cliques in the graph, and return a list of nodes.
        min_size: Minimum size of a clique
        max_size: Max size of a clique
        """
        if self.size() < min_size:
            return []

        graph = self
        if self.directed is True:
            graph = self.to_undirected()

        cliques = []

        # This is a dictionary of node value that contains an adjacent set
        # of nodes that are of the node that the key of the dictionary is connected
        # with.
        map_node = dict()

        for node in graph.nodes:
            if node.value in map_node:
                adj_set = map_node[node.value]
            else:
                adj_set = set()
            for child in node.children:
                adj_set.add(child.value)
                if child.value in map_node:
                    child_adj = map_node[child.value]
                    child_adj.add(node.value)
                    map_node[child.value] = child_adj
                else:
                    child_adj = set()
                    child_adj.add(node.value)
                    map_node[child.value] = child_adj
            map_node[node.value] = adj_set

        for node in graph.nodes:
            clique = [node.value]
            for child in node.children:
                child_adj = map_node[child.value]
                if node.value in child_adj:
                    clique.append(child.value)

            clique_size = len(clique)
            if clique_size >= min_size and clique_size <= max_size:
                cliques.append(clique)
        return cliques
