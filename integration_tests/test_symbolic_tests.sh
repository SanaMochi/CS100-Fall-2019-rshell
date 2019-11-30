#!/bin/sh

#exec 6>&1           # Link file descriptor #6 with stdout.
                    # Saves stdout.
#exec > data-file   # stdin replaced by file "data-file"
../src/rshell.cpp

g++ rshell.cpp -o rshell

[ -e "rshell" ]  # echo (True)
[ -f "header/command.h" ] # echo (True)
[ -d integration_tests ]  # echo (True)
[ -e asdf ] # echo (False)

./rshell

#exec 1>&6 6>&-      # Restore stdout and close file descriptor #6.
exit 0
