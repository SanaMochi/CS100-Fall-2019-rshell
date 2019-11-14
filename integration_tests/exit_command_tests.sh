#!/bin/sh
exec 6>&1           # Link file descriptor #6 with stdout.
                    # Saves stdout.
exec > data-file   # stdin replaced by file "data-file"
STR="echo it should work || exit || eecho fail && echo no && echo yes ; echo dont print this"
./rshell $STR		#when running from test needs (1) . , when running from shell needs (2) ..
exec 1>&6 6>&-      # Restore stdout and close file descriptor #6.
exit 0
