#!/bin/bash

PATH="$PATH:.test.cpp"
g++ integration_tests/test.cpp src/command.cpp src/component.cpp src/parser.cpp src/test.cpp -o test -std=c++11

echo "Should echo Alhamdulillah and ls"
(echo Alhamdulillah && ls) || (eecho fail && git status)

./test

exit 0
