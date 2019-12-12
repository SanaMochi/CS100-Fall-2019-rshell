#!/bin/bash

PATH="$PATH:.test.cpp"
g++ integration_tests/test.cpp src/command.cpp src/component.cpp src/parser.cpp src/test.cpp -o test -std=c++11

if test -e "rshell"; then
	echo "(True)"
fi
if test -f "header/command.h"; then
	echo "(True)"
fi
if test -d integration_tests; then
	echo "(True)"
fi

./test

exit 0
