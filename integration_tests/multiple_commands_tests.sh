#!/bin/sh
STR="echo hello && eecho fail && echo no && echo yes ; echo it works"
../main $STR
