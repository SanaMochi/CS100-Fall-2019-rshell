#!/bin/sh

test.cpp
g++ test.cpp -o test

cat < names.txt | tr A-Z a-z > newOutputFile10

./test

exit 0
