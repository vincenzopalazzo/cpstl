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

from src import GraphList, Node


def test_graph_init():
    """
    Simple test to init the graph and check the API
    of it.
    """
    graph = GraphList()
    assert graph is not None


def test_graph_add_edge():
    """
    Simple test to check the api to add an edge to graph.
    """
    graph = GraphList(directed=True)
    graph.add_edge(1, 2)
    graph.add_edge(2, 3)
    graph.add_edge(2, 4)
    assert graph.size() == 4


def test_dfs():
    """
    Simple test to test the dfs algorithm
    """
    graph = GraphList(directed=True)
    graph.add_edge(1, 2)
    graph.add_edge(2, 3)
    graph.add_edge(2, 4)
    assert graph.dfs() == [[1, 2], [2, 3, 4]]


def test_bfs():
    """
    Simple test to test the bfs algorithm
    """
    graph = GraphList(directed=True)
    graph.add_edge(1, 2)
    graph.add_edge(2, 3)
    graph.add_edge(2, 4)
    assert graph.bfs() == [[1, 2], [2, 3, 4]]


def test_mutate_from_directed_to_undirected_small():
    """"""
    graph = GraphList(directed=True)
    graph.add_edge(1, 2)

    undirected = graph.to_undirected()
    assert len(graph.edges()) * 2 == len(undirected.edges())


def test_mutate_from_directed_to_undirected_big():
    """"""
    graph = GraphList(directed=True)
    graph.add_edge(1, 2)
    graph.add_edge(2, 3)
    graph.add_edge(4, 5)

    undirected = graph.to_undirected()
    assert (len(graph.edges()) - 1) * 2 == len(undirected.edges()) - 1


def test_find_cliques_directed_empty():
    """
    Simple test to make sure that the clique algorithm works
    as best it can.
    """
    graph = GraphList(directed=True)
    graph.add_edge(1, 2)
    graph.add_edge(1, 3)
    graph.add_edge(1, 5)
    graph.add_edge(2, 3)
    graph.add_edge(2, 4)
    graph.add_edge(2, 6)
    graph.add_edge(3, 4)
    graph.add_edge(3, 6)
    graph.add_edge(4, 5)
    graph.add_edge(4, 6)

    # Find triangles in the graph (stupid algorithm)
    cliques = graph.cliques(min_size=3, max_size=3)
    assert len(cliques) == 0


def test_find_cliques_directed():
    """
    Simple test to make sure that the clique algorithm works
    as best it can
    """
    graph = GraphList(directed=True)
    graph.add_edge(1, 2)
    graph.add_edge(2, 3)
    graph.add_edge(3, 1)

    cliques = graph.cliques()
    assert len(cliques) == 1
