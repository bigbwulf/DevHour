CXXFLAGS = -Wall -pedantic -O2 -std=c++20
CC = g++

main: main.o
main.o: smartptrs.hpp templates.hpp lambdas.hpp templates.tcc


clean:
	rm -rf main
