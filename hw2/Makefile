all: lliststr_test assassin

lliststr_test: lliststr_test.cpp lliststr.o
	g++ -g -Wall lliststr.o lliststr_test.cpp -o lliststr_test

assassin: assassin.cpp lliststr.o
	g++ -g lliststr.o assassin.cpp -o assassin

lliststr.o: lliststr.h lliststr.cpp
	g++ -g -c lliststr.cpp -o lliststr.o


.PHONY: clean
clean:
	rm -rf 