CC = g++
CFLAGS = -Wall -Wextra -Werror -Wuninitialized
FILES = client/* server/*

all: build

build:
	mkdir -p build
	mkdir -p bin
	cd build && \
	$(CC) $(CFLAGS) ../client/*.cc -o ../bin/client && \
	$(CC) $(CFLAGS) ../server/*.cc -o ../bin/server && \
	cd ../
	rm -rf build

clean:
	rm -rf bin
	rm -rf build

googlestyle:
	clang-format -style=Google -i $(FILES)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ $(FILES)
