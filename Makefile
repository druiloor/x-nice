all:
	gcc -Wall -O2 X_wrapper.c -o X_wrapper

install:
	cp X_wrapper $(DESTDIR)/usr/bin/X
	chgrp wheel $(DESTDIR)/usr/bin/X
	chmod 4710 $(DESTDIR)/usr/bin/X
	chmod -s $(DESTDIR)/usr/bin/Xorg

uninstall:
	rm $(DESTDIR)/usr/bin/X
	ln -s $(DESTDIR)/usr/bin/Xorg $(DESTDIR)/usr/bin/X
	# Hmn dunno 'bout this
	chmod 4711 $(DESTDIR)/usr/bin/Xorg
	chmod u+s $(DESTDIR)/usr/bin/Xorg
