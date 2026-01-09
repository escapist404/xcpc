from random import *

T = 10
print(T)

for _ in range(T):
    n = randint(1, 10)
    m = randint(1, 10)
    p = 1024
    x = randint(0, p - 1)
    a = randint(0, p - 1)
    b = randint(0, p - 1)
    c = randint(0, p - 1)
    print(n, m, p, x, a, b, c)
