package hashset

import (
	"github.com/vincenzopalazzo/cpstl/go/datastructures/set"
)

type HashSet struct {
	buckets map[int64]set.ElemToHash
}

func NewHashSet() *HashSet {
	return &HashSet{buckets: make(map[int64]set.ElemToHash)}
}

func (instance *HashSet) Put(element set.ElemToHash) {
	hash := element.Hash()
	instance.buckets[hash] = element
}

func (instance *HashSet) Hash(element set.ElemToHash) bool {
	hash := element.Hash()
	_, ok := instance.buckets[hash]
	return ok
}

func (instance *HashSet) Size() int {
	return len(instance.buckets)
}

func (instance *HashSet) ToList() []set.ElemToHash {
	list := make([]set.ElemToHash, 0)
	for _, value := range instance.buckets {
		list = append(list, value)
	}
	return list
}
