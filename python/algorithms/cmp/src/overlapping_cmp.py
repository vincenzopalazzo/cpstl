"""
Clique Percolation Method to find overlapping communities in pure Python 3.

Version Code 0.1

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
from .graph_adj_list import GraphList, Node


class GraphOverlapping(GraphList):
    """
    Implementation of Graph data structure that contains some
    community detection to find overlapping between communities in the graph.
    """

    def __init__(self, directed: bool = True, clique_size: int = 3):
        """
        Constructor of Graph data structure with the overlapping community algorithm.

        directed: True is the graph is directed, False for not directed.
        clique: In the literature it is known as K, and it is called clique only for
        code readability.
        """
        GraphList.__init__(self.__class__, directed=directed)
        self.clique_size = clique_size


    def cmp(self) -> list:
        """
        Algorithm to apply Clique Percolation Method (CPM) over the graph,
        with K value specify in the constructor.
        It return a list of Communities that are Graphs
        """
        return do_cmp(self, self.cliques)


def do_cmp(graph: GraphList, clique_size: int = 3) -> list:
    """
    Core function to apply the Clique Percolation Method (CMP) over a graph,
    with cliques_size.

    graph: A grap implementation of cpstl library.
    clique_size: The size of the a single clique inside the graph.
    """
    cliques = graph.cliques(min_size = clique_size, max_size=clique_size)
    n_cliques = len(cliques)

    cliques_set = [set(clique) for clique in cliques]
