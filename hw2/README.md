# CS 104 HW2

- **Name**: Weihang Zhang
- **USC ID**: 3291880079
- **Email**: weihangz@usc.edu

Notes:

All files are in hw-weihangz/hw2 directory

Problems 1-4 are in hw2.txt. Open hw2.txt with Sublime 
editor.

Problem 5 is fullsort.cpp and needs an int main part for
it to compile. Write the int main part similar to the one
in the comment of fullsort.cpp and compile with
g++ -g -Wall fullsort.cpp -o fullsort

For Problem 6 and Problem 7, the lliststr_test and assasin
executables can be compiled using the Makefile I provided
by typing "make" into the terminal.

Problem 6 (files: lliststr.cpp lliststr.h lliststr_test.cpp)
can be compiled individually with 
g++ -g -c lliststr.cpp -o lliststr.o
g++ -g -Wall lliststr.o lliststr_test.cpp -o lliststr_test

Problem 7 (files: lliststr.cpp lliststr.h assassin.cpp)
can be compiled indiviually with 
g++ -g -c lliststr.cpp -o lliststr.o
g++ -g lliststr.o assassin.cpp -o assassin