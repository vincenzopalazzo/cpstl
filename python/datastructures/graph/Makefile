CC=python3
CHECK_SYNTAX=black
PIP=pip3

default: fmt
	$(CC) -m pytest --log-cli-level=DEBUG tests

fmt:
	$(CHECK_SYNTAX) .
