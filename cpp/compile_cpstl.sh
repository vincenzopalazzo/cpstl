#!/bin/bash

THIS_PATH="$(realpath "$0")"
THIS_DIR="$(dirname "$THIS_PATH")"

function runCommand() {
    printf "\n\n\n\Building $1"
    cd "$1"
    result=$(mkdir build)
    cd build
    cmake ..
    make
    result="$?"
    printf "\n"
    cd .. && rm -rf build
    return "$result"
}

# Find all files in THIS_DIR which end in .ino, .cpp, etc., as specified
# in the regular expression just below
find "$THIS_DIR" | grep -E "(CMakeList.txt)$"

result=$(find . -name build -exec rm -rf {} \;)
result=$(find . -name cmake-build-debug  -exec rm -rf {} \;)

while read -r line; do
    dir=$(cut -d' ' -f2- <<< "$line")
    runCommand "${dir%/*}"
    result="$?"
    if [ "$result" -ne 0 ] ; then
        echo "Failure $dir"
        exit "$result"
    else
        echo "Success: ${dir%*}"
    fi
    printf "\n"
done < <(find "$THIS_DIR" | grep -E ".*(.txt)$")