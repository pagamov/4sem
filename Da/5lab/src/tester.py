import random
import os, sys
import string
import subprocess
import time

def make_string(size_1, size_2):
    letters = string.ascii_lowercase
    letter = ["", ""]
    letter[0] = "".join(random.choice(letters) for _ in range(size_1))
    letter[1] = "".join(random.choice(letters) for _ in range(size_2))
    return letter


# main
# os.system("rm test/*.test")

# size = list(map(int, input().strip().split()))

lines = make_string(int(input()), int(input()))

file = open("test/test.test", "w")
file.write(lines[0] + '\n')
file.write(lines[1] + '\n')
file.close()

#
