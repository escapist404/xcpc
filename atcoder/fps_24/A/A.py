P = 998244353

D, N = [int(_) for _ in input().split()]

fac = [1] * (D + 1)
for i in range(1, D + 1):
    fac[i] = fac[i - 1] * i % P

ifac = [1] * D + [pow(fac[D], P - 2, P)] * 1
for i in range(D, 0, -1):
    ifac[i - 1] = ifac[i] * i % P

comb = lambda m, n: fac[m] * ifac[n] * ifac[m - n] % P if m >= n else 0

ans = 0
for j in range(0, D + 1):
    i = (N - D - 3 * j) // 2
    if 2 * i + 3 * j == N - D and 0 <= i <= D:
        ans += comb(D, i) * comb(D, j) % P
        ans %= P

print(ans)
