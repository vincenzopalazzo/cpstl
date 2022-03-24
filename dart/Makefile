CC=dart
FMT=format
ARGS="--help"
PROBLEM=

default: fmt

dep:
	$(CC) pub get

fmt:
	$(CC) $(FMT) .
	$(CC) analyze .

gen:
	$(CC) run build_runner build

clean:
	find . -name "*.graphql.dart" -type f -delete
	find . -name "*.graphql.g.dart" -type f -delete

check:
	$(CC) test