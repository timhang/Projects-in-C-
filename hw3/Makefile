all: stringparser

stringparser: stringparser.cpp lliststr.o stackstr.o
	g++ -g -Wall lliststr.o stackstr.o stringparser.cpp -o stringparser

stackstr.o: stackstr.cpp lliststr.o
	g++ -g -Wall -c stackstr.cpp -o stackstr.o

lliststr.o: lliststr.h lliststr.cpp
	g++ -g -Wall -c lliststr.cpp -o lliststr.o


.PHONY: clean
clean:
	rm -rf 