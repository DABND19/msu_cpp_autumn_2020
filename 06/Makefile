CC=g++
FLAGS=-std=c++17 -Wall

all: my_format

my_format: main.o Exception.hpp format.hpp test_runner.h
	$(CC) $(FLAGS) -o my_format main.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

test: my_format
	./my_format

clean:
	rm -rf *.o my_format