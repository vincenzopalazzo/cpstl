from src import GraphOverlapping

def test_init_graph():
    """
    Simple test to init the graph.
    """
    graph = GraphOverlapping(clique=2)
    graph.add_edge(1, 2)
    assert graph is not None
