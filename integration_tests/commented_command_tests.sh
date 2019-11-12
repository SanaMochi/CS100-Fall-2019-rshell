#!/bin/sh
STR="echo it works #&& eecho fail && echo no && echo yes ; echo it works"
../rshell $STR
