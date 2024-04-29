CC = gcc
CFLAGS = -Wall -fPIC -D DEBUG
LDFLAGS = -shared
TARGET_LIB = libcrest.so
SRC_LIB = cREST.c
HDR_LIB = cREST.h


all: $(TARGET_LIB) 

$(TARGET_LIB): $(SRC_LIB) $(HDR_LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f *.o
	rm -f $(TARGET_LIB)

install:
	# 如果需要安裝共享庫到系統，可以在這裡添加相應的安裝命令
	cp -f $(TARGET_LIB) /usr/lib
	chmod 0755 /usr/lib/$(TARGET_LIB)
	cp -f $(HDR_LIB) /usr/include
	ldconfig

uninstall:
	# 如果需要卸載共享庫，可以在這裡添加相應的卸載命令
	rm -f /usr/lib/$(TARGET_LIB)
	rm -f /usr/include/$(HDR_LIB)
