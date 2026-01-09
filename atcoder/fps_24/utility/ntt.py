P = 998244353
G = 3

def ntt(a: list[int], n: int, inverse = False):
    """
    Perform NTT on array a of length n (must be power of 2).
    If inverse=True, performs inverse NTT.
    Modifies a in-place.
    """
    rev = [0] * n
    for i in range(1, n):
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1))
    for i in range(n):
        if i < rev[i]:
            a[i], a[rev[i]] = a[rev[i]], a[i]
    
    omega = pow(pow(G, (P - 1) // n, P), P - 2, P) if inverse else pow(G, (P - 1) // n, P)
    
    block_size = 2
    while block_size <= n:
        half = block_size // 2
        w_step = pow(omega, n // block_size, P) if not inverse else pow(omega, n // block_size, P)
        for start in range(0, n, block_size):
            w = 1
            for j in range(half):
                u = a[start + j]
                v = (a[start + j + half] * w) % P
                a[start + j] = (u + v) % P
                a[start + j + half] = (u - v + P) % P
                w = (w * w_step) % P
        block_size *= 2
    
    if inverse:
        inv_n = pow(n, P - 2, P)
        for i in range(n):
            a[i] = (a[i] * inv_n) % P

def convolution(a: list[int], b: list[int]):
    """
    Compute the convolution of two arrays a and b using NTT.
    Returns the convolution result modulo MOD.
    """
    len_a = len(a)
    len_b = len(b)
    if len_a == 0 or len_b == 0:
        return []
    
    n = 1
    total_len = len_a + len_b - 1
    while n < total_len:
        n *= 2
    
    a_padded = a + [0] * (n - len_a)
    b_padded = b + [0] * (n - len_b)
    
    ntt(a_padded, n)
    ntt(b_padded, n)
    
    c = [(a_padded[i] * b_padded[i]) % P for i in range(n)]
    ntt(c, n, inverse = True)
    
    return c[ : total_len]