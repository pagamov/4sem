import random
import os, sys
import string
import subprocess
from time import time

import os.path
from os import path


def overlap(string1, string2, file):
    file_1 = open(file, "w")
    l_1 = len(string1)
    l_2 = len(string2)
    max_size = 0
    ansv = []
    for i in range(l_1):
        for j in range(i, l_1 + 1):
            ptr = string1[i:j]
            # print(ptr)

            if string2.find(ptr) >= 0:
                if j - i > max_size:
                    max_size = j - i
                    # clear(ansv)
                ansv.append(ptr)
    # print(max_size)
    file_1.write(str(max_size) + "\n")
    was = []
    if max_size == 0:
        file_1.write('\n')
    else:
        for word in sorted(ansv):
            if len(word) == max_size:
                if (word not in was):
                    file_1.write(word + '\n')
                    # print(word + "\n")
                    was.append(word)
    file_1.close()



def read_pattern(file):
    pattern = []
    file_1 = open(file, "r")

    pattern.append((file_1.readline()).replace("\n", ""))
    pattern.append((file_1.readline()).replace("\n", ""))

    file_1.close()
    return pattern



def make_string(size_1, size_2):
    # letters = string.ascii_lowercase
    letters = ['a','b','c','d','e','f','g','h']

    letter = ["", ""]
    letter[0] = "".join(random.choice(letters) for _ in range(size_1))
    letter[1] = "".join(random.choice(letters) for _ in range(size_2))
    return letter


# diff check_files(file_1, file_2):



# main

num = int(input())
lll = int(input())


for i in range(num):

    print(i)

    os.system("rm test/*.test")

    a = random.randint(0, lll)
    b = random.randint(0, lll)

    lines = make_string(a, b)

    file = open("test/test.test", "w")
    file.write(lines[0] + '\n')
    file.write(lines[1] + '\n')
    file.close()

    t_1 = time()
    os.system("valgrind ./main < test/test.test > test/check_main.test")
    print(str(time() - t_1) + " main " + str(a) + " " + str(b))

    # os.system("diff test/check_main.test test/check_a.test > test/res_diff.test")
    # os.system("echo 'hello' >> test/res_diff.test")

    f = open("test/check_main.test", "r")
    r = f.readline().replace("\n", "")

    if (int(r) < 0):
        print("hello")
        f.close()
        break;
