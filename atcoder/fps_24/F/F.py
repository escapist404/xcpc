P = 998244353

N = int(input())

print((pow(3, N, P) + pow(-1, N + 1, P)) * pow(4, P - 2, P) % P)