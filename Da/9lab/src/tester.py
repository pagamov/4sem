import random
import os, sys
import string
import subprocess
from time import time

def func (fileName, N, M):
    f = open(fileName, "w")
    f.write(str(N) + " " + str(M * N) + "\n")
    for i in range(N):
        for j in range(M):
            f.write(str(i + 1) + " " + str(j + 1) + " " + str(random.randint(1, 1000000)) + "\n")
    f.close();

# main
# os.system("make")

# func("test.txt", input(), input())

os.system("make")

N = input()

step = 100

for i in range(N):
    func("test.test", step * (i + 1), step * (i + 1))
    t_1 = time()
    print("res : ")
    os.system("./main < test.test")
    print("time : " + str(time() - t_1) + "\n" + "n: " + str((i + 1) * step) + " m: " + str((i + 1) * step) + "\n\n")

# os.system("rm main *.test")
