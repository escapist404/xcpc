import math

P = 998244353

N, M = [int(_) for _ in input().split()]

ifac = [1] * (M + 1)
ifac[M] = pow(math.factorial(M), P - 2, P)
for i in range(M, 0, -1):
    ifac[i - 1] = ifac[i] * i % P

f = [1] + [0] * N
for i in range(1, M + 1):
    g = [0] * (N + 1)
    for j in range(0, N + 1):
        for k in range(0, j + 1):
            g[j] += f[k] * (ifac[j - k] if j - k <= i else 0) % P
            g[j] %= P
    f = g

print(f[N] * math.factorial(N) % P)
