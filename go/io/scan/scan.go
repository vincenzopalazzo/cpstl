package scan

import (
	"bufio"
	"io"
)

// / DynamicScanner scanner be able to read a dynamic
// / buffer when the size of the stream is unknown.
type DynamicScanner struct {
	buf       []byte
	beg       int    // index of first data byte in buffer
	end       int    // index of after last data byte in buffer
	bytes     []byte // last line read
	err       error  // last error
	cachedErr error
}

// Error returns the last error.
func (g *DynamicScanner) Error() error {
	return g.err
}

// Text returns the last line read. The line ends with \n when a full line
// could be read, otherwise scanning was interrupted by a reading error.
// Returns an empty string after Scan() returned false.
func (g *DynamicScanner) Text() string {
	return string(g.bytes)
}

func (g *DynamicScanner) Bytes() []byte {
	return g.bytes
}

// Reset clears the buffer.
func (g *DynamicScanner) Reset() {
	g.err = nil
	g.cachedErr = nil
	g.bytes = []byte{}
	g.beg = 0
	g.end = 0
}

// Scan reads bytes until a \n is found or the reading ends with an error.
// A call to Text() returns the last line read. Scan returns false if an error
// was returned by Read. The error can be retrieved by calling Error().
func (g *DynamicScanner) Scan(r io.Reader) bool {
	if g.err != nil {
		return false
	}
	idx := g.beg
	for {
		if g.cachedErr != nil {
			if g.beg != g.end {
				g.bytes = g.buf[g.beg:g.end]
				g.beg = g.end
				return true
			}
			g.err = g.cachedErr
			g.bytes = []byte{}
			return false
		}

		for i := idx; i < g.end; i++ {
			// catch the end of the stream!
			// FIXME: inject the contains function to
			// parse all the stream!
			if g.buf[i] == '\n' && g.buf[i+1] == '\n' {
				g.bytes = g.buf[g.beg:i]
				return false
			}
			// FIXME: it is possible split the token by `\n` but it is not
			// what we want
		}

		if g.end == len(g.buf) {
			if len(g.buf) == 0 {
				g.buf = make([]byte, bufio.MaxScanTokenSize)
			} else {
				buf := make([]byte, 2*cap(g.buf))
				copy(buf, g.buf)
				g.buf = buf
			}
		}
		n, err := r.Read(g.buf[g.end:])
		g.cachedErr = err
		idx = g.end
		g.end += n
	}

}
