all: Thanksgiving.o

Thanksgiving.o: Thanksgiving.cpp LengthMismatch.o
	g++ -std=c++11 -g -Wall -c LengthMismatch.o Thanksgiving.cpp -o Thanksgiving.o

LengthMismatch.o: LengthMismatch.h LengthMismatch.cpp
	g++ -std=c++11 -g -Wall -c LengthMismatch.cpp -o LengthMismatch.o


.PHONY: clean
clean:
	rm -rf 