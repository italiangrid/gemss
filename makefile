compile:
	make -C src/c
	make -C src/java
	make -C src/nailgun-0.7.1

install:
	make -C src/c install
	make -C src/java install
	make -C scripts install
	make -C lib install
	mkdir -p /usr/local/yamss/bin
	mkdir -p /usr/local/yamss/lib
	cp -a src/nailgun-0.7.1/nailgun-0.7.1.jar /usr/local/yamss/lib
	cp -a src/nailgun-0.7.1/ng /usr/local/yamss/bin

buildinstall:
	rm -rf /tmp/gemssbuildroot
	make -C src/c buildinstall
	make -C src/java buildinstall
	make -C scripts buildinstall
	make -C lib buildinstall
	mkdir -p /tmp/gemssbuildroot/usr/local/yamss/bin
	mkdir -p /tmp/gemssbuildroot/usr/local/yamss/lib
	cp -a src/nailgun-0.7.1/nailgun-0.7.1.jar /tmp/gemssbuildroot/usr/local/yamss/lib
	cp -a src/nailgun-0.7.1/ng /tmp/gemssbuildroot/usr/local/yamss/bin

clean:
	make -C src/c clean
	make -C src/java clean
	make -C src/nailgun-0.7.1 clean

rpm: compile
	make -C rpm
