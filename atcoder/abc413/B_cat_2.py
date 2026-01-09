N = int(input())
S = [_ for _ in range(N)]

for i in range(N):
    S[i] = input()

P = dict()

for i in range(N):
    for j in range(N):
        if i == j:
            continue
        P[S[i] + S[j]] = 1

print(len(P))
