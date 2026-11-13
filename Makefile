all:
	gcc -Wall -O2 X_wrapper.c -o X_wrapper
	strip --strip-all X_wrapper

install:
	# Backup will be: /usr/bin/X~
	install --backup X_wrapper $(DESTDIR)/usr/bin/X
	#chgrp wheel $(DESTDIR)/usr/bin/X
	# operator has primary group root
	chmod 4750 $(DESTDIR)/usr/bin/X
	#chmod -s $(DESTDIR)/usr/bin/Xorg
	#chmod -s $(DESTDIR)/usr/libexec/Xorg
	#chmod -s $(DESTDIR)/usr/libexec/Xorg.wrap

uninstall:
	# Hmn dunno 'bout this: why not just reinstall xorg
	rm $(DESTDIR)/usr/bin/X
	ln -s $(DESTDIR)/usr/bin/Xorg $(DESTDIR)/usr/bin/X
	#chmod 4711 $(DESTDIR)/usr/bin/Xorg
	chmod u+s $(DESTDIR)/usr/bin/Xorg
