#!/bin/sh

PATH="$PATH:.test.cpp"
g++ integration_tests/test.cpp src/command.cpp src/component.cpp src/parser.cpp src/test.cpp -o test -std=c++11

echo hi >> newOutputFile

./test

exit 0
