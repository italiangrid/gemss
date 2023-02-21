all: yamssDB2Query.class yamssDB2Update.class

yamssDB2Query.class: yamssDB2Query.java
	javac -classpath ../../lib/db2jcc4.jar yamssDB2Query.java

yamssDB2Update.class: yamssDB2Update.java
	javac -classpath ../../lib/db2jcc4.jar yamssDB2Update.java

clean:
	rm -f yamssDB2Query.class yamssDB2Update.class

install:
	mkdir -p /usr/local/yamss/lib
	cp -a yamssDB2Query.class yamssDB2Update.class /usr/local/yamss/lib

buildinstall:
	mkdir -p /tmp/gemssbuildroot/usr/local/yamss/lib
	cp -a yamssDB2Query.class yamssDB2Update.class /tmp/gemssbuildroot/usr/local/yamss/lib
