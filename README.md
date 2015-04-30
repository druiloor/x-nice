Just edit /usr/X11R6/bin/startx and add something like this at the top:

export X_NICE="-10"

To make it work save it as X_wrapper.c, and do (something like) this:

gcc -Wall -02 X_wrapper.c -o X_wrapper
rm /usr/bin/X
cp X_wrapper /usr/bin/X
chgrp wheel /usr/bin/X
chmod 4710 /usr/bin/X
chmod -s `which Xorg` 
