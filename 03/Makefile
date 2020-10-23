CC=g++
FLAGS=-std=c++17

all: my_matrix

my_matrix: main.o Matrix.o
	$(CC) $(FLAGS) -o my_matrix main.o Matrix.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

Matrix.o: Matrix.h Matrix.cpp
	$(CC) $(FLAGS) -c Matrix.cpp

test: my_matrix
	./my_matrix

clean:
	rm -rf *.o my_matrix