P = 998244353
G = 3

def ntt(a: list[int], n: int, inverse = False):
    """
    Perform NTT on array a of length n (must be power of 2).
    If inverse = True, performs inverse NTT.
    Modifies a in-place.
    """
    rev = [0] * n
    for i in range(1, n):
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1))
    for (i, v) in enumerate(rev):
        if i < v:
            a[i], a[v] = a[v], a[i]
    
    omega = pow(pow(G, (P - 1) // n, P), P - 2, P) if inverse else pow(G, (P - 1) // n, P)
    
    block_size = 2
    while block_size <= n:
        half = block_size >> 1
        w_step = pow(omega, n // block_size, P)
        for start in range(0, n, block_size):
            w = 1
            for j in range(half):
                u = a[start + j]
                v = (a[start + j + half] * w) % P
                a[start + j] = (u + v) % P
                a[start + j + half] = (u - v + P) % P
                w *= w_step
                w %= P
        block_size <<= 1
    
    if inverse:
        inv_n = pow(n, P - 2, P)
        for i in range(n):
            a[i] *= inv_n
            a[i] %= P

def convolution(a: list[int], b: list[int]):
    """
    Compute the convolution of two arrays a and b using NTT.
    Returns the convolution result modulo P.
    """
    s = len(a)
    t = len(b)
    
    if min(s, t) <= 60:
        c = [0] * (s + t - 1)
        for i in range(s):
            if i & 0b111 == 0:
                for j in range(t):
                    c[i + j] += a[i] * b[j]
                    c[i + j] %= P
            else:
                for j in range(t):
                    c[i + j] += a[i] * b[j]
        return [i % P for i in c]
    
    if s == 0 or t == 0:
        return []
    
    n = 1 << (s + t - 2).bit_length()

    ra = a + [0] * (n - s)
    rb = b + [0] * (n - t)
    
    ntt(ra, n)
    ntt(rb, n)
    
    c = [(ra[i] * rb[i]) % P for i in range(n)]
    ntt(c, n, inverse = True)
    
    return c[ : s + t - 1]

N, M, L = [int(_) for _ in input().split()]
A = [int(_) for _ in input().split()]
B = {int(_) for _ in input().split()}

im = pow(M, P - 2, P)
V = [0] * (2 * N)
for i in A:
    V[i] = im

f = [1] + [0] * (2 * N - 1)

def derive(L: int, R: int):
    if L + 1 == R:
        if L in B:
            f[L] = 0
        return
    
    mid = (L + R) // 2
    derive(L, mid)
    if L < min(mid, N):        
        u = f[L : min(mid, N)]
        v = V[ : R - L]
        w = convolution(u, v)
        for i in range(mid, R):
            f[i] += w[i - L]
            f[i] %= P
    derive(mid, R)

derive(0, 2 * N)
print(sum(f[N : ]) % P)
    