CC=g++
FLAGS=-std=c++17

all: my_allocator

my_parser: main.o TokenParser.o
	$(CC) $(FLAGS) -o my_parser main.o TokenParser.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

TokenParser.o: TokenParser.h TokenParser.cpp
	$(CC) $(FLAGS) -c TokenParser.cpp

test: my_parser
	./my_parser

clean:
	rm -rf *.o my_allocator