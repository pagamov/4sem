import random
import os, sys
import string
import subprocess
from time import time

MAXINT = 1000000000000000

def make_test(file, res, number):

    print("min number : 0 and max number " + str(10) + "^20")

    f = open(file, "w")
    r = open(res, "w")
    oper = ["+","-","/","*","^","<",">","="]
    # oper = ["^"]

    for i in range(number):

        now_oper = random.choice(oper)

        num_a = random.randint(0, MAXINT) * random.randint(1, MAXINT) * random.randint(1, MAXINT) * random.randint(1, MAXINT) * random.randint(1, MAXINT)
        num_b = random.randint(0, MAXINT) * random.randint(1, MAXINT) * random.randint(1, MAXINT) * random.randint(1, MAXINT) * random.randint(1, MAXINT)
        # num_b = 1000
        f.write(str(num_a) + "\n")
        f.write(str(num_b) + "\n")



        if (now_oper == "+"):
            f.write("+" + "\n")
            r.write(str(num_a + num_b) + "\n")

        elif (now_oper == "-"):
            f.write("-" + "\n")
            if num_a >= num_b:
                r.write(str(num_a - num_b) + "\n")
            else:
                r.write("Error\n")

        elif (now_oper == "/"):
            f.write("/" + "\n")
            if num_b != 0:
                r.write(str(num_a / num_b) + "\n")
            else:
                r.write("Error\n")

        elif (now_oper == "*"):
            f.write("*" + "\n")
            r.write(str(num_a * num_b) + "\n")

        elif (now_oper == "^"):
            f.write("^" + "\n")
            if num_a != 0 and num_b != 0:
                r.write(str(num_a ** num_b) + "\n")
            else:
                r.write("Error")

        elif (now_oper == "<"):
            f.write("<" + "\n")
            if num_a < num_b:
                r.write("true\n")
            else:
                r.write("false\n")

        elif (now_oper == ">"):
            f.write(">" + "\n")
            if num_a > num_b:
                r.write("true\n")
            else:
                r.write("false\n")

        elif (now_oper == "="):
            f.write("=" + "\n")
            if num_a == num_b:
                r.write("true\n")
            else:
                r.write("false\n")
        # print(str(i) + " done ")

    f.close()
    r.close()

# main
os.system("mkdir test; rm test/*.test")

num = int(input())

print("number count " + str(num))

t_p = time()
make_test("test/test.test", "test/res_py.test", num)
print("time python : " + str(time() - t_p))

t_c = time()
os.system("./main < test/test.test > test/res_c.test")
print("time c++ : " + str(time() - t_c))

# os.system("diff test/res_py.test test/res_c.test > test/diff.test")
#
# f = open("test/diff.test", "r")
# if ((f.readline()).replace("\n", "") != ""):
#     print("error")
#     f.close()
#     break;

#
