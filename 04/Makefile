CC=g++
FLAGS=-std=c++17 -Wall

all: big_integer

big_integer: main.o BigInt.o Vector.h test_runner.h
	$(CC) $(FLAGS) -o big_integer main.o BigInt.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

BigInt.o: BigInt.h BigInt.cpp
	$(CC) $(FLAGS) -c BigInt.cpp

test: big_integer
	./big_integer

clean:
	rm -rf *.o big_integer