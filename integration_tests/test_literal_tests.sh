#!/bin/bash

test.cpp

g++ test.cpp -o test

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
