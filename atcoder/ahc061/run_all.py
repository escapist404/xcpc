#!/usr/bin/env python3
TESTCASE_COUNT = 100
import sys, os

print("\033[95mrun_all.py Compiling monte_carlo_grok.cpp...\033[0m")
os.system("g++ -O2 -std=c++23 monte_carlo_grok.cpp -o build -DNDEBUG")
for id in range(0, TESTCASE_COUNT):
    input_file = f"in/{id:04d}.txt"
    print("\033[95mrun_all.py executing with input file: " + input_file + "\033[0m")
    os.system(f"cargo run -r --bin tester ./build < {input_file} > out.txt")
    # input("Press Enter to continue to the next test case...")

# 0054
