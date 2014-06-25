install:
	mkdir -p /usr/local/yamss/bin
	cp -a yamss* /usr/local/yamss/bin
	rm -f /usr/local/yamss/bin/yamssmonitor
	rm -f /usr/local/yamss/bin/yamss.*
	cp -a yamssmonitor /etc/init.d
	cp -a yamss.sh yamss.csh /etc/profile.d

buildinstall:
	mkdir -p /tmp/gemssbuildroot/usr/local/yamss/bin
	cp -a yamss* /tmp/gemssbuildroot/usr/local/yamss/bin
	rm -f /tmp/gemssbuildroot/usr/local/yamss/bin/yamssmonitor
	rm -f /tmp/gemssbuildroot/usr/local/yamss/bin/yamss.*
	mkdir -p /tmp/gemssbuildroot/etc/init.d
	mkdir -p /tmp/gemssbuildroot/etc/profile.d
	cp -a yamssmonitor /tmp/gemssbuildroot/etc/init.d
	cp -a yamss.sh yamss.csh /tmp/gemssbuildroot/etc/profile.d
