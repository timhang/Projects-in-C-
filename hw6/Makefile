all: search crawler

crawler: crawler.cpp
	g++ -std=c++11 -g -Wall crawler.cpp -o crawler

search: search.cpp webpage.o
	g++ -std=c++11 -g -Wall webpage.o search.cpp -o search

webpage.o: webpage.cpp
	g++ -std=c++11 -g -Wall -c webpage.cpp -o webpage.o


.PHONY: clean
clean:
	rm -rf 