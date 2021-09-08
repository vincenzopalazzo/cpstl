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


def test_find_kcliques_undirected():
    """
    Simple test to make sure that the cliques algorithm make the
    job on an undirected graph.

    Example taken from: https://stackoverflow.com/a/59339555/14933807
    """
    graph = GraphList()
    graph.add_edge(1, 0)
    graph.add_edge(1, 4)
    graph.add_edge(0, 4)
    graph.add_edge(1, 2)
    graph.add_edge(2, 3)
    graph.add_edge(3, 4)
    graph.add_edge(3, 5)
    cliques = graph.bron_kerbosch()
    graph.logger.debug(cliques)
    assert len(cliques) == 5


def test_find_kcliques_directed():
    """
    Simple test to make sure that the cliques algorithm make the
    job on an undirected graph.
    """
    graph = GraphList(directed=True)
    graph.add_edge(1, 2)
    graph.add_edge(2, 3)
    graph.add_edge(3, 1)
    cliques = graph.bron_kerbosch()
    assert len(cliques) == 1


def test_connected_component():
    """
    Test to check if the algorithm to check the
    connected component, make the right job.
    """
    pass
