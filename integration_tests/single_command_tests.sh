#!/bin/sh

exec 6>&1           # Link file descriptor #6 with stdout.
                    # Saves stdout.
exec > data-file   # stdin replaced by file "data-file"
./rshell echo hello world
./rshell echo it works
exec 1>&6 6>&-      # Restore stdout and close file descriptor #6.
exit 0
