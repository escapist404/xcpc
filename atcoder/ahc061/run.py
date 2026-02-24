#!/usr/bin/env python3
import sys, os

print("\033[95mrun.py Compiling monte_carlo_grok.cpp...\033[0m")
os.system("g++ -O2 -std=c++23 monte_carlo_grok.cpp -o build")
print("\033[95mrun.py executing with input file: " + sys.argv[1] + "\033[0m")
os.system(f"cargo run -r --bin tester ./build < {sys.argv[1]} > out.txt")
