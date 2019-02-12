all: search

search: search.cpp webpage.o
	g++ -g -Wall webpage.o search.cpp -o search

webpage.o: webpage.cpp
	g++ -g -Wall -c webpage.cpp -o webpage.o

.PHONY: clean
clean:
	rm -rf 