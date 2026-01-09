import math

P = 998244353

N, M = [int(_) for _ in input().split()]

fac = [1] * (M + 2)
for i in range(1, M + 2):
    fac[i] = fac[i - 1] * i % P

ifac = [1] * (M + 1) + [pow(fac[M + 1], P - 2, P)] * 1
for i in range(M + 1, 0, -1):
    ifac[i - 1] = ifac[i] * i % P

comb = lambda m, n: fac[m] * ifac[n] * ifac[m - n] % P if m >= n else 0

ans = 0
if N >= 2:
    for i in range(M - N + 2):
        ans += pow(-1, i, P) * comb(i + N - 2, N - 2) * comb(M - i + 1, N)
        ans %= P
else:
    ans = (M + 1) % P

print(ans * math.factorial(N) % P)
