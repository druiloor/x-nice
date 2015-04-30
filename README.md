Just edit /usr/bin/startx and add something like this at the top:

export X_NICE="-10"

And do (something like) this:

make
make install
