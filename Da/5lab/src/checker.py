import random
import os, sys
import string
import subprocess
from time import time


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

# main
www = read_pattern("test/test.test")
# print(www)

t_1 = time()
overlap(www[0], www[1], "test/check_a.test")
print(time() - t_1)
# overlap("", "", "test/check_a.test")

t_1 = time()
os.system("./main < test/test.test > test/check_main.test")
print(time() - t_1)

# os.system("diff test/check_main.test test/check_a.test")
