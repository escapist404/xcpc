N = int(input())
S, T = input(), input()
for i in range(N):
    if S[i] == T[i]:
        print("Yes")
        exit()
print("No")
