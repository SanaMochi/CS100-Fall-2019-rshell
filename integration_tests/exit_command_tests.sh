#!/bin/sh

PATH="$PATH:.test.cpp"
g++ integration_tests/test.cpp src/command.cpp src/component.cpp src/parser.cpp src/test.cpp -o test -std=c++11

echo it should work || exit || eecho fail && echo no && echo yes ; echo dont print this

./test
exit 0
