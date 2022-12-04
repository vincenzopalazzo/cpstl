CC=go
FMT=gofmt
NAME=test

default: fmt

fmt:
	$(CC) fmt ./...

lint:
	golangci-lint run

check:
	$(CC) test -v ./...

check_fmt:
	gofmt -e ../.

dep:
	$(CC) mod vendor
