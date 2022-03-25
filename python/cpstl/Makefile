CC=poetry
FMT=black

default: fmt

fmt:
	$(FMT) .

dep:
	$(CC) lock;
	$(CC) install;
	$(CC) export -f requirements.txt > requirements.txt

check:
	pytest .

build:
	$(CC) build

release: build
	$(CC) publish