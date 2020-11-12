CC=g++
FLAGS=-std=c++17 -Wall

all: my_serializer

my_serializer: main.o Serializers.hpp test_runner.h
	$(CC) $(FLAGS) -o my_serializer main.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

test: my_serializer
	./my_serializer

clean:
	rm -rf *.o my_serializer