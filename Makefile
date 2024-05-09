CC = gcc
PREFIX ?= /usr/local
CFLAGS = -Wall -fPIC -D DEBUG -I$(PREFIX)/include -I$(PREFIX)/include/cjson
LDFLAGS = -shared -L$(PREFIX)/lib -lcjson
TARGET_LIB = libcrest.so
SRC_LIB = cREST.c
HDR_LIB = cREST.h

INSTALL_INCLUDE_PATH = $(PREFIX)/include
INSTALL_LIBRARY_PATH = $(PREFIX)/lib

all: $(TARGET_LIB)

$(TARGET_LIB): $(SRC_LIB) $(HDR_LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f *.o
	rm -f $(TARGET_LIB)

install:
	mkdir -p $(INSTALL_LIBRARY_PATH) $(INSTALL_INCLUDE_PATH)
	cp -f $(TARGET_LIB) $(INSTALL_LIBRARY_PATH)
	chmod 0755 $(INSTALL_LIBRARY_PATH)/$(TARGET_LIB)
	cp -f $(HDR_LIB) $(INSTALL_INCLUDE_PATH)
	ldconfig

uninstall:
	rm -f $(INSTALL_LIBRARY_PATH)/$(TARGET_LIB)
	rm -f $(INSTALL_INCLUDE_PATH)/$(HDR_LIB)
