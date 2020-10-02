CC = g++
CCFLAGS = -std=c++11 -Wall -pedantic
###____###
main 		: code/main.cpp ; $(CC) $(CCFLAGS) -o main code/main.cpp

clean		: ; rm main

tar 		: ; mkdir solution ; cp code/*.hpp code/*.cpp code/makefile solution ; tar -cf solution.tar solution

tar2 		: ; mkdir solution ; cp code2/*.hpp code2/*.cpp code2/makefile solution ; tar -cf solution.tar solution

tard		: solution/ solution.tar ; rm -r solution solution.tar

prod		: ; python tester.py
# cleant		: ; rm test/*.test
# check		: ; python checker.py
valgrind 	: ; valgrind ./main < test/test.test > test/res.test
# -s --leak-check=full --track-origins=yes
# callgrind 	: ; valgrind --tool=callgrind ./main < test/test.test > test/res.test
# cache 		: ; kcachegrind
# sol 		: ; $(CC) $(CCFLAGS) -o sol solution.cpp
# prod : ; python production.py
###___###
