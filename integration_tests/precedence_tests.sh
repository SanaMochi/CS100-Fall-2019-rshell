#!/bin/bash

test.cpp

g++ test.cpp -o test

echo "Should echo Alhamdulillah and ls"
(echo Alhamdulillah && ls) || (eecho fail && git status)

./test

exit 0
