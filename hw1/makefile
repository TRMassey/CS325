all: prog

prog: algorithms.o main.o
	g++ -o prog algorithms.o main.o
	
main.o: main.cpp
	g++ -c main.cpp
	
algorithms.o: algorithms.cpp algorithms.hpp
	g++ -c algorithms.cpp

clean:	

