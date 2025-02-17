#!/bin/bash

# Get the current directory
THIS_DIR="$(pwd)"

# Find all files in THIS_DIR which end in .ino, .cpp, etc., as specified
# in the regular expression just below
FILE_LIST="$(find "$THIS_DIR" | grep -E ".*(\.ino|\.cpp|\.c|\.h|\.hpp|\.hh)$")"

echo -e "Files found to check the code format = \n\"\"\"\n$FILE_LIST\n\"\"\""

# Format each file.
# - NB: do NOT put quotes around `$FILE_LIST` below or else the `clang-format` command will
#   mistakenly see the entire blob of newline-separated file names as a SINGLE file name instead
#   of as a new-line separated list of *many* file names!
clang-format --dry-run --Werror --style=file $FILE_LIST