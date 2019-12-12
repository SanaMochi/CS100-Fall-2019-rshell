#!/bin/sh

test.cpp
g++ test.cpp -o test

echo hi >> newOutputFile

./test

exit 0
