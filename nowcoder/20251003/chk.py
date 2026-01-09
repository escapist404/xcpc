from os import *

ANS_SRC = "fb.cpp"
OUT_SRC = "f.cpp"

system(f"g++ {ANS_SRC} -o ans")
system(f"g++ {OUT_SRC} -o out")

c = 0
while True:
    system("python3 ./gen.py > ./in.txt")
    system("./ans < ./in.txt > ./ans.txt")
    system("./out < ./in.txt > ./out.txt")
    if system("diff ./ans.txt ./out.txt") != 0:
        print("WA")
        break
    c += 1
    print("OK", c)
