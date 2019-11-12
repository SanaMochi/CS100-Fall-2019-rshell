#!/bin/sh
exec 6>&1           # Link file descriptor #6 with stdout.
                    # Saves stdout.
exec > data-file   # stdin replaced by file "data-file"
STR="echo hello && eecho fail && echo no && echo yes ; echo it works"
../rshell $STR
exec 1>&6 6>&-      # Restore stdout and close file descriptor #6.
