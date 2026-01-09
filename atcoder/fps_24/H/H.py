P = 998244353

def factorial(n: int):
    result = 1
    for i in range(1, n + 1):
        result *= i
        result %= P
    return result


N, M = [int(_) for _ in input().split()]

f0 = factorial(N + M) * pow(factorial(N), P - 2, P) * pow(factorial(M), P - 2, P) % P
f1 = factorial(N + M - 1) * pow(factorial(N), P - 2, P) * pow(factorial(M - 1), P - 2, P) % P

g0 = pow(2, M, P)
g1 = pow(2, M - 1, P)

print((f0 * g0 - f1 * g1) % P)
