CC = g++
CCFLAGS = -std=c++11 -Wall -pedantic -O3
###____###
main 		: code/main.cpp ; $(CC) $(CCFLAGS) -o main code/main.cpp
clean		: ; rm main
tar 		: ; mkdir solution ; cp code/*.cpp code/makefile solution ; tar -cf solution.tar solution
tard		: solution/ solution.tar ; rm -r solution solution.tar
prod		: ; python tester.py
valgrind 	: ; valgrind ./main < test/test.test > test/res.test
###___###
