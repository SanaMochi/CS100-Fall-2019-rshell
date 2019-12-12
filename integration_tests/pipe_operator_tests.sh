#!/bin/sh

PATH="$PATH:.test.cpp"
g++ integration_tests/test.cpp src/command.cpp src/component.cpp src/parser.cpp src/test.cpp -o test -std=c++11

cat < names.txt | tr A-Z a-z > newOutputFile10

./test

exit 0
