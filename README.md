BTW if you are teaking a desktop you might want to try setting the
X-server to run with a negative `nice' value. I read on KernelTrap "-10"
should be a good setting. However it might be a little tricky to actually
set it to that, there for i wrote a little "wrapper" which had it
hardcoded (default to "-1" but trivially edited):
<http://groups.google.nl/groups?q=menno+X+wrapper+group:alt.os.linux.slackware>

Now i wanted to see if it realy helped any, so i added some code which
reads the X_NICE environment value and thus makes it easy to adjust.
Just edit /usr/X11R6/bin/startx and add something like this at the top:

export X_NICE="-10"

To make work it save it as X_wrapper.c, and do (something like) this:
gcc -Wall -02 X_wrapper.c -o X_wrapper
rm /usr/X11R6/bin/X
cp X_wrapper /usr/X11R6/bin/X
chmod 4755 /usr/X11R6/bin/X
(Better yet, set the last comment to something more restrictive.)
And you can: chmod -s `which XFree86` 
