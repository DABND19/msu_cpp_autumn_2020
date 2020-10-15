CC=g++
FLAGS=-std=c++17

all: my_allocator

my_parser: main.o Parser.o
	$(CC) $(FLAGS) -o my_parser main.o Parser.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

Parser.o: Parser.cpp Parser.h
	$(CC) $(FLAGS) -c Parser.cpp

test: my_parser
	./my_parser

clean:
	rm -rf *.o my_allocator