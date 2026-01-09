P = 998244353

N, M, L = [int(_) for _ in input().split()]
A = [int(_) for _ in input().split()]
B = {int(_) for _ in input().split()}

im = pow(M, P - 2, P)
f = [1] + [0] * (2 * N - 1)

for i in range(2 * N):
    if i in B:
        continue
    for j in A:
        if i - j >= 0 and i - j < N:
            f[i] += f[i - j] * im % P
            f[i] %= P

print(sum(f[N : ]) % P)
