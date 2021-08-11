"""
Clique Percolation Method (CPM) implementation in python3 for the
graph library igraph.

Version code 0.1

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

from igraph import Graph

def clique_percolation_method(graph: Graph, clique_size: int = 3) -> list:
    """
    Function that implements the Clique Percolation Method (CPM) algorithm for
    finding overlapping communities within networks.

    graph: Undirected graph implementation of library igraph
    clique_size: Size of one sigle clique.
    """
    communities = []

    ## Finding the cliques in a graph
    cliques = graph.cliques(min=clique_size, max=clique_size)
    n_cliques = len(cliques)

    clique_graph = Graph()
    components = clique_graph.decompose()

    # CREATING COMMUNITIES
    for component in components:
        members_list = [list(cliques[i["name"]]) for i in component.vs]
        this_community = [item for sublist in members_list for item in sublist]
        communities.append(list(set(this_community)))

    if attribute is not None:
        communities_with_names = list()
        for community in communities:
            communities_with_names.append([graph.vs[element][attribute] for element in community])
        communities = communities_with_names

    return []
