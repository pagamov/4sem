CC = g++
CCFLAGS = -std=c++11 -Wall -pedantic -g
###____###
main 		: code2/main.cpp code2/*.hpp ; $(CC) $(CCFLAGS) -o main code2/main.cpp



clean		: ; rm main
tar 		: ; mkdir solution ; cp code2/*.hpp code2/*.cpp code2/makefile solution ; tar -cf solution.tar solution
tard		: solution/ solution.tar ; rm -r solution solution.tar
test		: ; python tester.py
cleant		: ; rm test/*.test
check		: ; python checker.py
valgrind 	: ; valgrind ./main < test/test.test > test/res.test
# -s --leak-check=full --track-origins=yes
callgrind 	: ; valgrind --tool=callgrind ./main < test/test.test > test/res.test
cache 		: ; kcachegrind
sol 		: ; $(CC) $(CCFLAGS) -o sol solution.cpp
prod : ; python production.py
###___###
