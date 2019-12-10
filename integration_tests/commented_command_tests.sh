#!/bin/sh

test.cpp
g++ test.cpp -o test

echo it works #&& eecho fail && echo no && echo yes ; echo it works
./test

exit 0
