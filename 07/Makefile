CC=g++
FLAGS=-std=c++17 -Wall

all: my_vector

my_vector: main.o Vector.hpp test_runner.h
	$(CC) $(FLAGS) -o my_vector main.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

test: my_vector
	valgrind ./my_vector

clean:
	rm -rf *.o my_vector