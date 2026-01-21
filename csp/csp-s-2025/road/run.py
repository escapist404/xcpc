from os import system

PROB_NAME = "road"

system(f"g++ {PROB_NAME}.cpp -o {PROB_NAME} -O2 -std=c++17")

TEST_NAME = ["road1", "road2", "road3", "road4"]
for name in TEST_NAME:
    system(f"./{PROB_NAME} < ./{name}.in > ./{name}.out")
    system(f"diff ./{name}.out ./{name}.ans -s -w -B")
