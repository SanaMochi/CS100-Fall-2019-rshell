#!/bin/sh

exec 6>&1           # Link file descriptor #6 with stdout.
                    # Saves stdout.
exec > data-file   # stdin replaced by file "data-file"

if [ -e "rshell" ]
then echo (True)
if [ -f "header/command.h" ]
then echo (True)

exec 1>&6 6>&-      # Restore stdout and close file descriptor #6.
exit 0
