#!/bin/sh
test.cpp
g++ test.cpp -o test

echo hello && eecho fail && echo no || echo yes && echo it works

./test
