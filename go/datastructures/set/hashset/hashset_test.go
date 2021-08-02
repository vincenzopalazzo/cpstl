package hashset

import (
	"fmt"
	"hash/fnv"
	"testing"

	"github.com/stretchr/testify/assert"
)

type TestBucket struct {
	value int
}

func NewBucket(value int) *TestBucket {
	return &TestBucket{value: value}
}

func (instance *TestBucket) Hash() int64 {
	h := fnv.New32a()
	h.Write([]byte(fmt.Sprint(instance.value)))
	return int64(h.Sum32())
}

func TestHashSetInit(t *testing.T) {
	set := NewHashSet()

	assert.Equal(t, 0, set.Size())
}

func TestHashInsertOne(t *testing.T) {
	set := NewHashSet()

	set.Put(NewBucket(1))
	set.Put(NewBucket(2))

	assert.Equal(t, 2, set.Size())
}

func TestHashInsertTwo(t *testing.T) {
	set := NewHashSet()

	set.Put(NewBucket(1))
	set.Put(NewBucket(1))

	assert.Equal(t, 1, set.Size())
}
