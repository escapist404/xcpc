P = 998244353

N, M, L = [int(_) for _ in input().split()]

f = [1] + [0] * N

for m in range(1, M + 1):
    for i in range(m, N + 1):
        f[i] += f[i - m]
        f[i] %= P
    
    if m >= L:
        print(f[N] % P)
        for i in range(N, m - L, -1):
            f[i] -= f[i - m + L - 1]
            f[i] %= P
