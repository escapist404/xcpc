T = int(input())

while T > 0:
    T -= 1
    N = int(input())
    A = sorted([int(_) for _ in input().split()], key = lambda x: abs(x))
    
    if len({abs(_) for _ in A}) == 1:
        s = abs(A[0])
        if A.count(s) == N or A.count(s) == 0 or A.count(s) == N // 2 or A.count(s) == (N + 1) // 2:
            print("Yes")
        else:
            print("No")
        continue
    
    ok = True
    for i in range(1, N - 1):
        if A[i - 1] * A[i + 1] != A[i] * A[i]:
            ok = False
            break
    print("Yes" if ok else "No")

