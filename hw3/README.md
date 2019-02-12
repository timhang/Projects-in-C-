# CS 104 HW3

- **Name**: Weihang Zhang
- **USC ID**: 3291880079
- **Email**: weihangz@usc.edu

Notes:

All files are in hw-weihangz/hw3 directory

Problems 1-3 are in hw3.txt. Open hw3.txt with Sublime 
editor.

Problem 4 is stackstr.cpp and needs a dummy main part for
it to compile. Write the int main part like the stack_test.cpp
file I provided and compile with
g++ -g -Wall stack_test.cpp -o stack_test

For Problem 5, the stringparser executable 
can be compiled using the Makefile I provided
by typing "make stringparser" into the terminal.
OR, enter:
g++ -g -Wall -c lliststr.cpp -o lliststr.o
g++ -g -Wall -c stackstr.cpp -o stackstr.o
g++ -g -Wall lliststr.o stackstr.o stringparser.cpp -o stringparser
in successions in the terminal to produce the executable.
Then, enter: ./stringparser input1.txt output1.txt to run.
Remember to always provide an input file and a output file
in the command line.