CC = gcc
SRC_PROGRAM = main.c
INC = -I /usr/include   #include headers的位置
LIB = -lcrest -lfcgi          #include libraries的位置
program = rest_ctrl
TARGET_BIN = /usr/local/bin/

all: $(program)

$(program): $(SRC_PROGRAM) 
	$(CC) -D DEBUG -o $@ $< ${INC} ${LIB}

clean:
	rm -f *.o
	rm -f $(program)

install:
	# 如果需要安裝共享庫到系統，可以在這裡添加相應的安裝命令
	cp $(program) $(TARGET_BIN)

uninstall:
	# 如果需要卸載共享庫，可以在這裡添加相應的卸載命令
	rm $(TARGET_BIN)$(program)
