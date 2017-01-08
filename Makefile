CC = gcc -std=gnu99
FLAG_LIB = -lncurses
FLAG_DEBUG = -Wall -Werror -ggdb
FLAG_INC = -I inc
SOURCES:=$(shell find src -type f | grep -v "main.c")

all:
	mkdir -p bin/
	$(CC) $(SOURCES) src/main.c -o bin/game $(FLAG_LIB) $(FLAG_INC)

debug: 
	mkdir -p bin/
	$(CC) $(SOURCES) src/main.c -o bin/debug $(FLAG_LIB) $(FLAG_INC) $(FLAG_DEBUG) 

clean:
	rm -rf bin/*

.PHONY: test
test:
	mkdir -p bin/test
	for path in $$(ls test/*.c); do key=$$(basename $$path .c); echo "instal: $$path";\
		$$($(CC) $(SOURCES) $$path -o bin/test/$$key $(FLAG_LIB) $(FLAG_INC) $(FLAG_DEBUG)); \
	done;\
	echo "run tests";\
	for path in $$(ls test/*.c); do key=$$(basename $$path .c);\
		bin/test/$$key;\
	done

format: 
	astyle --style="k&r" $(shell find src -type f) $(shell find inc -type f)
	rm $(find . -type f | grep '\.orig')
