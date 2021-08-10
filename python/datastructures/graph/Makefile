CC=python3
CHECK_SYNTAX=black
PIP=pip3

default: fmt
	$(CC) -m pytest -v tests

fmt:
	$(CHECK_SYNTAX) .
