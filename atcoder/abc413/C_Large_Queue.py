import collections

Q = int(input())
D = collections.deque()

while Q > 0:
    argv = [int(_) for _ in input().split()]
    if argv[0] == 1:
        c, x = argv[1 : 3]
        D.append([c, x])
    else:
        k = argv[1]
        s = 0
        while k > D[0][0]:
            k -= D[0][0]
            s += D[0][0] * D[0][1]
            D.popleft()
        D[0][0] -= k
        s += k * D[0][1]
        print(s)
    
    Q -= 1
