P = 998244353

N, M, S = [int(_) for _ in input().split()]

fac = [1] * (N + S + 1)
for i in range(1, N + S + 1):
    fac[i] = fac[i - 1] * i % P

ifac = [1] * (N + S) + [pow(fac[N + S], P - 2, P)] * 1
for i in range(N + S, 0, -1):
    ifac[i - 1] = ifac[i] * i % P
    
comb = lambda m, n: fac[m] * ifac[n] * ifac[m - n] if m >= n else 0

ans = 0
for i in range(N + 1):
    ans += pow(-1, i, P) * comb(N, i) * comb(S - i * (M + 1) + N - 1, N - 1) % P
    ans %= P
    
print(ans)
