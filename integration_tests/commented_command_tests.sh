#!/bin/sh

#PATH="$PATH:.test.cpp"
PATH="$PATH:.test.cpp"
g++ integration_tests/test.cpp src/command.cpp src/component.cpp src/parser.cpp src/test.cpp -o test -std=c++11

echo it works #&& eecho fail && echo no && echo yes ; echo it works
./test

exit 0
