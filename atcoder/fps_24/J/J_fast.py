from array import array

mod = 998244353
MOD = 998244353
IMAG = 911660635
IIMAG = 86583718
INV2 = 499122177
rate2 = array('I',
              [0, 911660635, 509520358, 369330050, 332049552, 983190778, 123842337, 238493703, 975955924, 603855026,
               856644456, 131300601, 842657263, 730768835, 942482514, 806263778, 151565301, 510815449, 503497456,
               743006876, 741047443, 56250497, 867605899, 0])
irate2 = array('I',
               [0, 86583718, 372528824, 373294451, 645684063, 112220581, 692852209, 155456985, 797128860, 90816748,
                860285882, 927414960, 354738543, 109331171, 293255632, 535113200, 308540755, 121186627, 608385704,
                438932459, 359477183, 824071951, 103369235, 0])
rate3 = array('I',
              [0, 372528824, 337190230, 454590761, 816400692, 578227951, 180142363, 83780245, 6597683, 70046822,
               623238099, 183021267, 402682409, 631680428, 344509872, 689220186, 365017329, 774342554, 729444058,
               102986190, 128751033, 395565204, 0])
irate3 = array('I',
               [0, 509520358, 929031873, 170256584, 839780419, 282974284, 395914482, 444904435, 72135471, 638914820,
                66769500, 771127074, 985925487, 262319669, 262341272, 625870173, 768022760, 859816005, 914661783,
                430819711, 272774365, 530924681, 0])

def butterfly(a):
    n = len(a)
    if n == 0:
        return
    h = (n - 1).bit_length()
    le = 0
    while le < h:
        if h - le == 1:
            p = 1 << (h - le - 1)
            rot = 1
            for s in range(1 << le):
                offset = s << (h - le)
                for i in range(p):
                    l = a[i + offset]
                    r = a[i + offset + p] * rot
                    a[i + offset] = (l + r) % MOD
                    a[i + offset + p] = (l - r) % MOD
                rot *= rate2[(~s & -~s).bit_length()]
                rot %= MOD
            le += 1
        else:
            p = 1 << (h - le - 2)
            rot = 1
            for s in range(1 << le):
                rot2 = rot * rot % MOD
                rot3 = rot2 * rot % MOD
                offset = s << (h - le)
                for i in range(p):
                    a0 = a[i + offset]
                    a1 = a[i + offset + p] * rot
                    a2 = a[i + offset + p * 2] * rot2
                    a3 = a[i + offset + p * 3] * rot3
                    a1na3imag = (a1 - a3) % MOD * IMAG
                    a[i + offset] = (a0 + a2 + a1 + a3) % MOD
                    a[i + offset + p] = (a0 + a2 - a1 - a3) % MOD
                    a[i + offset + p * 2] = (a0 - a2 + a1na3imag) % MOD
                    a[i + offset + p * 3] = (a0 - a2 - a1na3imag) % MOD
                rot *= rate3[(~s & -~s).bit_length()]
                rot %= MOD
            le += 2


def butterfly_inv(a):
    n = len(a)
    if n == 0:
        return
    h = (n - 1).bit_length()
    le = h
    while le:
        if le == 1:
            p = 1 << (h - le)
            irot = 1
            for s in range(1 << (le - 1)):
                offset = s << (h - le + 1)
                for i in range(p):
                    l = a[i + offset]
                    r = a[i + offset + p]
                    a[i + offset] = (l + r) % MOD
                    a[i + offset + p] = (l - r) * irot % MOD
                irot *= irate2[(~s & -~s).bit_length()]
                irot %= MOD
            le -= 1
        else:
            p = 1 << (h - le)
            irot = 1
            for s in range(1 << (le - 2)):
                irot2 = irot * irot % MOD
                irot3 = irot2 * irot % MOD
                offset = s << (h - le + 2)
                for i in range(p):
                    a0 = a[i + offset]
                    a1 = a[i + offset + p]
                    a2 = a[i + offset + p * 2]
                    a3 = a[i + offset + p * 3]
                    a2na3iimag = (a2 - a3) * IIMAG % MOD
                    a[i + offset] = (a0 + a1 + a2 + a3) % MOD
                    a[i + offset + p] = (a0 - a1 + a2na3iimag) * irot % MOD
                    a[i + offset + p * 2] = (a0 + a1 - a2 - a3) * irot2 % MOD
                    a[i + offset + p * 3] = (a0 - a1 - a2na3iimag) * irot3 % MOD
                irot *= irate3[(~s & -~s).bit_length()]
                irot %= MOD
            le -= 2


# ==== FPS 在线卷积 ====
class FPSOnlineConvolution:
    def __init__(self):
        self.f = []
        self.g = []
        self.h = []
        self.iz = []
        self.f_inv = []
        self.g_inv = []
        self.p = 0

    def query(self, fi, gi):
        fi %= MOD
        gi %= MOD
        if self.p == 0:
            self.f = [fi]
            self.g = [gi]
            self.h = [fi * gi % MOD]
            self.p = 1
            return self.h[0]
        p = self.p
        z = 0
        while (p & (1 << z)) == 0:
            z += 1
        if p == (1 << z):
            need = p * 2 - len(self.f)
            if need > 0:
                self.f += [0] * need
                self.g += [0] * need
                self.h += [0] * need
        self.f[p] = fi
        self.g[p] = gi
        l = p - (1 << z)
        m = p
        r = p + (1 << z)
        tmp3 = [0] * (r - l)
        if l == 0:
            self.f_inv.append([])
            self.g_inv.append([])
            self.iz.append(pow(r - l, MOD - 2, MOD))
        for rp in range(2):
            self.f, self.g = self.g, self.f
            self.f_inv, self.g_inv = self.g_inv, self.f_inv
            if l == 0 and rp == 1:
                break
            tmp1 = [0] * (r - l)
            tmp2 = [0] * (r - l)
            for i in range(l, m):
                tmp1[i - l] = self.f[i]
            butterfly(tmp1)
            if l == 0:
                for i in range(r - l):
                    if i == 0:
                        continue
                    if i >= m:
                        break
                    tmp2[i] = self.g[i]
                butterfly(tmp2)
            else:
                if not self.g_inv[z]:
                    size = 1 << (z + 1)
                    self.g_inv[z] = [0] * size
                    for i in range(size):
                        self.g_inv[z][i] = self.g[i] if i > 0 else 0
                    butterfly(self.g_inv[z])
                tmp2 = self.g_inv[z][:]
            for i in range(r - l):
                tmp3[i] = (tmp3[i] + tmp1[i] * tmp2[i]) % MOD
        butterfly_inv(tmp3)
        iz = self.iz[z]
        for i in range(m, r):
            self.h[i] = (self.h[i] + tmp3[i - l] * iz) % MOD
        self.h[p] = (self.h[p] + self.f[0] * self.g[p] + self.f[p] * self.g[0]) % MOD
        val = self.h[p]
        self.p += 1
        return val

from sys import stdin
input = lambda: stdin.readline().rstrip()

def solve():
    N, M, L = map(int, input().split())
    faces = list(map(int, input().split()))
    traps = list(map(int, input().split()))

    A = [0] * N
    invM = pow(M, MOD - 2, MOD)
    for a in faces:
        if 1 <= a <= N:
            A[a - 1] = (A[a - 1] + invM) % MOD

    B = [0] * (N + 1)
    for x in traps:
        if 1 <= x <= N - 1:
            B[x] = 1

    oc = FPSOnlineConvolution()

    ans = 1
    fr = 1
    for i in range(N - 1):
        tmp = oc.query(A[i], fr)
        if B[i + 1]:
            ans = (ans - tmp) % MOD
            tmp = 0
        fr = tmp
    print(ans)

if __name__ == "__main__":
    solve()