def divide_and_conquer(S):
    L = len(S)
    if L == 1:
        return S
    LHS = divide_and_conquer(S[0 : L // 2])
    RHS = divide_and_conquer(S[L // 2 : L])
    if LHS > RHS:
        LHS, RHS = RHS, LHS
    return LHS + RHS

T = int(input())

while T > 0:
    T -= 1

    N = int(input())
    A = [int(_) for _ in input().split()]

    A = divide_and_conquer(A)

    for i in A:
        print(i, end = " ")
    print()
