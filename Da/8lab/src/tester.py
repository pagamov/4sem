import random
import os, sys
import string
import subprocess
from time import time

STEP = 10000

def make_test(file, num):
    f = open(file, "w")
    # n = random.randint(1, 1000 * num)
    n = STEP * num
    f.write(str(n) + "\n")
    for i in range(n):
        f.write(str(random.randint(-100000, 100000)) + "\n")
    f.close()

# main
os.system("make")

for i in range(int(input())):
    make_test("test.test", i + 1)

    t_1 = time()
    os.system("./main < test.test")
    print("time : " + str(time() - t_1) + "\n" + "number of sides : " + str((i + 1) * STEP) + "\n\n")

os.system("rm main *.test")
#
