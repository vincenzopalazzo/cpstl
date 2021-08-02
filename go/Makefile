CC=go
FMT=gofmt
NAME=go-cpstl

default: fmt check

fmt:
	$(CC) fmt ./...

check:
	$(CC) test -v github.com/vincenzopalazzo/cpstl/go/...
