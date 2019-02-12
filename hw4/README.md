# CS 104 HW4

- **Name**: Weihang Zhang
- **USC ID**: 3291880079
- **Email**: weihangz@usc.edu

Notes:

All files are in hw-weihangz/hw4 directory

Problems 1 is in hw4.pdf

For Problem 2, the search executable 
can be compiled using the Makefile I provided
by typing "make search" into the terminal.
OR, enter:
	g++ -g -Wall -c webpage.cpp -o webpage.o
	g++ -g -Wall webpage.o search.cpp -o search
in successions in the terminal to produce the executable.
Then, enter: 
./search data/index.txt data/query.txt data/output.txt to run.
Remember to always provide an index file, a query file, 
and a output file in the command line.