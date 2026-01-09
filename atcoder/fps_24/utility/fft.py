# NTT (Number Theoretic Transform) implementation using butterfly transformation
# Modulus: 998244353 (a common prime for NTT, 2^23 * 119 + 1)
# Primitive root: 3

MOD = 998244353
G = 3  # Primitive root modulo MOD

def mod_pow(base, exp, mod):
    """Modular exponentiation: base^exp mod mod"""
    result = 1
    base %= mod
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp //= 2
    return result

def ntt(a, n, inverse=False):
    """
    Perform NTT on array a of length n (must be power of 2).
    If inverse=True, performs inverse NTT.
    Modifies a in-place.
    """
    # Bit-reversal permutation
    rev = [0] * n
    for i in range(1, n):
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (n >> 1))
    for i in range(n):
        if i < rev[i]:
            a[i], a[rev[i]] = a[rev[i]], a[i]
    
    # Precompute omega
    omega = mod_pow(G, (MOD - 1) // n, MOD)
    if inverse:
        omega = mod_pow(omega, MOD - 2, MOD)
    
    # Butterfly transformations
    block_size = 2
    while block_size <= n:
        half = block_size // 2
        w_step = mod_pow(omega, n // block_size, MOD) if not inverse else mod_pow(omega, n // block_size, MOD)
        for start in range(0, n, block_size):
            w = 1
            for j in range(half):
                u = a[start + j]
                v = (a[start + j + half] * w) % MOD
                a[start + j] = (u + v) % MOD
                a[start + j + half] = (u - v + MOD) % MOD
                w = (w * w_step) % MOD
        block_size *= 2
    
    if inverse:
        # Normalize by dividing by n
        inv_n = mod_pow(n, MOD - 2, MOD)
        for i in range(n):
            a[i] = (a[i] * inv_n) % MOD

def convolve(a, b):
    """
    Compute the convolution of two arrays a and b using NTT.
    Returns the convolution result modulo MOD.
    """
    len_a = len(a)
    len_b = len(b)
    if len_a == 0 or len_b == 0:
        return []
    
    # Find the smallest power of 2 >= len_a + len_b - 1
    n = 1
    total_len = len_a + len_b - 1
    while n < total_len:
        n *= 2
    
    # Pad a and b with zeros to length n
    a_padded = a + [0] * (n - len_a)
    b_padded = b + [0] * (n - len_b)
    
    # Perform NTT on a and b
    ntt(a_padded, n)
    ntt(b_padded, n)
    
    # Point-wise multiplication
    c = [(a_padded[i] * b_padded[i]) % MOD for i in range(n)]
    
    # Inverse NTT
    ntt(c, n, inverse=True)
    
    # Trim the result to the actual convolution length
    return c[:total_len]

# Example usage:
# a = [1, 2, 3, 4]
# b = [5, 6, 7, 8]
# result = convolve(a, b)
# print(result)  # Should be the convolution: [5, 16, 34, 60, 61, 52, 32] mod MOD, but since small, unchanged