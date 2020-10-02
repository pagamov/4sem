CC = g++
CCFLAGS = -std=c++11 -Wall -pedantic -O3 -g
###____###
main 		: code/main.cpp code/*.hpp ; $(CC) $(CCFLAGS) -o main code/main.cpp
clean		: ; rm -r main *.dSYM
tar 		: ; mkdir solution ; cp code/*.cpp code/*.hpp code/makefile solution ; tar -cf solution.tar solution
tard		: solution/ solution.tar ; rm -r solution solution.tar
prod		: ; python tester.py
valgrind 	: ; valgrind --leak-check=full -v ./main
###___###
