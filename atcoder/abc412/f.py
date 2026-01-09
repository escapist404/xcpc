P = 998244353

N, C = [int(i) for i in input().split()]
A = [int(i) for i in input().split()]

inverse = lambda base: pow(base, P - 2, P)

A[C - 1] += 1
ref = A[C - 1]
A = sorted(A)
S = sum(A) - 1

U, V = 0, S + 1

for i in reversed(range(N)):
    V -= A[i]
    f = (U + S) * inverse(S - V) % P
    U += A[i] * f
    if A[i] == ref:
        print(f)
        break

