CC = g++
CCFLAGS = -std=c++14 -Wall -pedantic -Werror -Wno-sign-compare -Wno-long-long
###____###
all : main
main : code/main.cpp code/bigint.hpp ; $(CC) $(CCFLAGS) -o main code/main.cpp
clean		: ; rm -r main code/*.o
tar 		: ; mkdir solution ; cp code/*.hpp code/*.cpp code/makefile solution ; tar -cf solution.tar solution
tard		: solution/ solution.tar ; rm -r solution solution.tar
prod		: ; python tester.py
# cleant		: ; rm test/*.test
# check		: ; python checker.py
# valgrind 	: ; valgrind ./main < test/test.test > test/res.test
# -s --leak-check=full --track-origins=yes
# callgrind 	: ; valgrind --tool=callgrind ./main < test/test.test > test/res.test
# cache 		: ; kcachegrind
# sol 		: ; $(CC) $(CCFLAGS) -o sol solution.cpp
# prod : ; python production.py
###___###
