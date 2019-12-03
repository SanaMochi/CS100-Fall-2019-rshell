#!/bin/sh

test.cpp
g++ test.cpp -o test

echo it should work || exit || eecho fail && echo no && echo yes ; echo dont print this

./test
exit 0
