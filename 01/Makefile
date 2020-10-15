CC=g++
FLAGS=-std=c++17

all: test

test: main.o allocator.o
	$(CC) $(FLAGS) -o test main.o allocator.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

allocator.o: allocator.cpp allocator.h
	$(CC) $(FLAGS) -c allocator.cpp

clean:
	rm -rf *.o my_allocator
