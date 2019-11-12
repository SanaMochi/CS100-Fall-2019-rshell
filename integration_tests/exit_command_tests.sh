#!/bin/sh
STR="echo it works || exit || eecho fail && echo no && echo yes ; echo dont print this"
../rshell $STR
