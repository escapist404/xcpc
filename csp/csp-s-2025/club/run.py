from os import system

PROB_NAME = "club"

system(f"g++ {PROB_NAME}.cpp -o {PROB_NAME} -O2 -std=c++14")

TEST_NAME = ["club1", "club2", "club3", "club4", "club5"]
for name in TEST_NAME:
    system(f"./{PROB_NAME} < ./{name}.in > ./{name}.out")
    system(f"diff ./{name}.out ./{name}.ans -s -w -B")
