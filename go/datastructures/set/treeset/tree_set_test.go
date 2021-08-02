package treeset

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestTreeSetInt(t *testing.T) {
	set := NewTreeSet()
	assert.Equal(t, uint64(0), set.Size())
}
