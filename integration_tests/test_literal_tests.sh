#!/bin/sh

#exec 6>&1           # Link file descriptor #6 with stdout.
                    # Saves stdout.
#exec > data-file   # stdin replaced by file "data-file"
../src/rshell.cpp

g++ rshell.cpp -o rshell

test -e "rshell" # then echo (True)
test -f "header/command.h" # then echo (True)
test -d integration_tests # then echo (True)
test -e asdf  # then echo (False)

./rshell

#exec 1>&6 6>&-      # Restore stdout and close file descriptor #6.
exit 0
