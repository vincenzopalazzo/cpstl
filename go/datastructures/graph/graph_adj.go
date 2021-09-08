package graph

type Node struct {
	Value interface{}
	AdiacencyList []*Node
}

type GraphAdj struct {
	directed bool
	nodes []*Node
}

func NewGraphAdj(directed bool) Graph {
	return &GraphAdj{directed: directed, nodes: make([]*Node, 0)}
}

func (instance GraphAdj) IsDirected() bool {
	return instance.directed
}

func (instance GraphAdj) AddEdge(u interface{}, v interface{}) {}

func (instance GraphAdj) DoBFS() []interface{} {}

func (instance GraphAdj) DoDFS() []interface{} {}
