#!/bin/sh

PATH="$PATH:.test.cpp"
g++ integration_tests/test.cpp src/command.cpp src/component.cpp src/parser.cpp src/test.cpp -o test -std=c++11

[ -e "rshell" ]  # echo (True)
[ -f "header/command.h" ] # echo (True)
[ -d integration_tests ]  # echo (True)
[ -e asdf ] # echo (False)

./test

exit 0
