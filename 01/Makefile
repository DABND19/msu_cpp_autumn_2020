CC=g++
FLAGS=-std=c++17

all: my_allocator

my_allocator: main.o allocator.o
	$(CC) $(FLAGS) -o my_allocator main.o allocator.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

allocator.o: allocator.cpp allocator.h
	$(CC) $(FLAGS) -c allocator.cpp

clean:
	rm -rf *.o my_allocator
