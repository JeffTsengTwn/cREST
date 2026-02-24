CC = gcc
SRC_PROGRAM = main.c redfish_handler.c
INC = -I /usr/include -I ..  #include headers的位置
LIB = -lcrest -lfcgi         #include libraries的位置
program = redfish_ctrl
TARGET_BIN = /usr/local/bin/

all: $(program)

$(program): $(SRC_PROGRAM) redfish_handler.h
	$(CC) -D DEBUG -o $@ $(SRC_PROGRAM) ${INC} ${LIB}

clean:
	rm -f *.o
	rm -f $(program)

install:
	cp $(program) $(TARGET_BIN)

uninstall:
	rm -f $(TARGET_BIN)$(program)
