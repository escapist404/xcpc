from random import randint

T = 1

print(T)

for _ in range(T):
    N, K = 200000, 6
    print(N, K)
    for i in range(N):
        print(randint(1, 9), end = "")
    print()
