CC = g++
CFLAGS = -Wall -Wextra -Werror -Wuninitialized
FILES = client/* server/*

all: build

build: clean
	mkdir -p build
	mkdir -p bin
	cd build && \
	$(CC) $(CFLAGS) ../client/*.cc -o ../bin/client && \
	$(CC) $(CFLAGS) ../server/*.cc -o ../bin/server && \
	cd ../
	rm -rf build

clean:
	rm -rf bin

googlestyle:
	clang-format -style=Google -i $(FILES)
