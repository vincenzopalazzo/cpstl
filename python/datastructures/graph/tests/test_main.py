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
    assert graph.bfs() != [[1, 2], [2, 3, 4]]
