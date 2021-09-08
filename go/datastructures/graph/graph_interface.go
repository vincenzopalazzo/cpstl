package graph


type Graph interface {

	// Check if the graph is directed
	IsDirected() bool

	// Adding a edge from u -> v if the graph
	// is directed, otherwise put another edge from
	// v -> u.
	AddEdge(u interface{}, v interface{})

	// Apply the BFS algorithm
	DoBFS() []interface{}

	// Apply the DFS algorithm
	DoDFS() []interface{}
}
