import random
import os, sys
import string
import subprocess
from time import time

MAXINT = 100000

def make_test(file):
    f = open(file, "w")
    n = random.randint(1, 100)
    w = random.randint(1, 300)
    f.write(str(n) + " " + str(w) + "\n")
    for i in range(n):
        f.write(str(random.randint(1, 10)) + " " + str(random.randint(1, 10)) + "\n")
    f.close()

# main
os.system("g++ -std=c++11 code/main.cpp -o a1")
os.system("g++ -std=c++11 code2/main.cpp -o a2")

num = int(input("test? "))

for i in range(num):

    make_test("test.test")

    t_1 = time()
    os.system("./a1 < test.test")
    print(str(time() - t_1) + " main \n\n")

    t_2 = time()
    os.system("./a2 < test.test")
    print(str(time() - t_2) + " sub \n\n")


os.system("rm a1 a2 *.test")
#
