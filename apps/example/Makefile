CC = gcc
SRC_PROGRAM = main.c
INC = -I /usr/local/include -I /usr/local/include/cjson   # location of include headers
LIB = -lcrest -lcjson -lfcgi          # location of libraries to link
program = rest_ctrl
TARGET_BIN = /usr/local/bin/

all: $(program)

$(program): $(SRC_PROGRAM) 
	$(CC) -D DEBUG -o $@ $< ${INC} ${LIB}

clean:
	rm -f *.o
	rm -f $(program)

install:
	# Add any additional install commands here if the shared library needs to be installed on the system
	cp $(program) $(TARGET_BIN)

uninstall:
	# Add any additional uninstall commands here if the shared library needs to be removed
	rm $(TARGET_BIN)$(program)
