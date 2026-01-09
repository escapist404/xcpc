# FPS 24: 24 Problems on Formal Power Series

## A - Snack

在 $D$ 天时间内你一共花了 $N$ 元，每天要么花 $1$ 元，要么花 $3$ 元，要么花 $4$ 元，要么花 $6$ 元。求花钱方案的数量，对 $998244353$ 取模。两个花钱方案不同当且仅当某一天花的数量不一样。

---

构造生成函数：

$$
\left(x + x^3 + x^4 + x^6\right)^{D}
$$

即求 $x^N$ 的系数。化简得到：

$$
\begin{aligned}
\left(x + x^3 + x^4 + x^6\right)^{D} &= x^D \left(1 + x^2 + x^3 + x^5\right)^D \\
&= x^D \left(1 + x^2\right)^D \left(1 + x^3\right)^D
\end{aligned}
$$

于是：

$$
\begin{aligned}
\left(x + x^3 + x^4 + x^6\right)^{D} \left[x^N\right] &= \left(1 + x^2\right)^D \left(1 + x^3\right)^D \left[x^{N - D}\right] \\
&= \left[\sum_{i = 0}^D \binom{D}{i} x^{2i}\right] \left[\sum_{j = 0}^D \binom{D}{j} x^{3j}\right] \left[x^{N - D}\right] \\
&= \sum_{2i + 3j = N - D}^{i, j \le D} \binom{D}{i} \binom{D}{j}
\end{aligned}
$$

时间复杂度 $O(D)$。本题引入了普通生成函数。

---

```py
P = 998244353

D, N = [int(_) for _ in input().split()]

fac = [1] * (D + 1)
for i in range(1, D + 1):
    fac[i] = fac[i - 1] * i % P

ifac = [1] * D + [pow(fac[D], P - 2, P)] * 1
for i in range(D, 0, -1):
    ifac[i - 1] = ifac[i] * i % P

comb = lambda m, n: fac[m] * ifac[n] * ifac[m - n] % P if m >= n else 0

ans = 0
for j in range(0, D + 1):
    i = (N - D - 3 * j) // 2
    if 2 * i + 3 * j == N - D and 0 <= i <= D:
        ans += comb(D, i) * comb(D, j) % P
        ans %= P

print(ans)
```

## B - Tuple of Integers

给定非负整数 $N$，求满足以下条件的非负整数四元组 $\left(a, b, c, d\right)$ 的个数，对 $998244353$ 取模。

* $a + b + c + d = N$
* $a \in \left\{0, 1\right\}$
* $b \in \left\{0, 1, 2\right\}$
* $c$ 是偶数
* $d$ 是 $3$ 的倍数

---

构造生成函数：

$$
\left(1 + x\right) \left(1 + x + x^3\right) \left(1 + x^2 + x^4 + \cdots\right) \left(1 + x^3 + x^6 + \cdots\right)
$$

其中 $x^N$ 的系数即为所求。考虑：

$$
\begin{aligned}
\left(1 + x^2 + x^4 + \cdots\right) &= \frac{1}{1 - x^2} \\
\left(1 + x^3 + x^6 + \cdots\right) &= \frac{1}{1 - x^3} \\
\end{aligned}
$$

于是：

$$
\begin{aligned}
\left(1 + x\right) \left(1 + x + x^3\right) \left(1 + x^2 + x^4 + \cdots\right) \left(1 + x^3 + x^6 + \cdots\right) &= \frac{\left(1 + x\right)\left(1 + x + x^2\right)}{\left(1 - x^2\right)\left(1 - x^3\right)} \\
&= \frac{1}{\left(1 - x\right)^2} \\
&= \left(1 + x + x^2 + \cdots\right)^2
\end{aligned}
$$

一般地，考虑如下 $\frac{1}{\left(1 - x\right)^k}$ 的式子：

$$
\begin{aligned}
\frac{1}{\left(1 - x\right)^k} &= \left(1 + x + x^2 + \cdots\right)^k \\
&= \sum_{i = 0}^{\infty} \binom{i + k - 1} {k - 1} x^i
\end{aligned}
$$

考虑隔板法即可证出。代入 $k = 2, i = N$ 可得答案为 $N + 1$。

时间复杂度 $O(1)$。

---

```py
P = 998244353

N = int(input())
print((N + 1) % P)
```

## C - Sequence

求长度为 $N$，值取不大于 $M$ 的非负整数，且整个序列的元素和为 $S$ 的序列个数，对 $998244353$ 取模。

---

构造生成函数：

$$
\left(1 + x + x^2 + \cdots + x^M\right)^N
$$

其中 $x^S$ 的系数即为所求。考虑：

$$
\begin{aligned}
\left(1 + x + x^2 + \cdots + x^M\right)^N &= \left(\frac{1 - x^{M + 1}}{1 - x}\right)^N \\
&= \left(1 - x^{M + 1}\right)^N \left(1 + x + x^2 + \cdots\right)^N
\end{aligned}
$$

又考虑如下项的系数：

$$
\left(1 - x^{M + 1}\right)^N = \sum_{i = 0}^N \left(-1\right)^i \binom{N}{i} x^{i \left(M + 1\right)} \\
\left(1 + x + x^2 + \cdots\right)^N = \sum_{i = 0}^\infty \binom{i + N - 1}{N - 1} x^i
$$

于是原函数 $x^S$ 的系数为：

$$
\left[x^S\right] = \sum_{0 \le i \le N} \left(-1\right)^i \binom{N}{i} \binom{S - i\left(M + 1\right) + N - 1}{N - 1}
$$

时间复杂度 $O(N)$。

---

```py
P = 998244353

N, M, S = [int(_) for _ in input().split()]

fac = [1] * (N + S + 1)
for i in range(1, N + S + 1):
    fac[i] = fac[i - 1] * i % P

ifac = [1] * (N + S) + [pow(fac[N + S], P - 2, P)] * 1
for i in range(N + S, 0, -1):
    ifac[i - 1] = ifac[i] * i % P
    
comb = lambda m, n: fac[m] * ifac[n] * ifac[m - n] if m >= n else 0

ans = 0
for i in range(N + 1):
    ans += pow(-1, i, P) * comb(N, i) * comb(S - i * (M + 1) + N - 1, N - 1) % P
    ans %= P
    
print(ans)
```

## D - Sequence 2

求满足如下条件的长度为 $N$ 的序列 $A = \left(a_1, a_2, \cdots, a_N\right)$ 的数量，对 $998244353$ 取模：

* $0 \le a_i \le M$；
* 记 $B = \left(b_1, b_2, \cdots, b_N\right)$ 为 $A$ 的严格递增排列，希望 $B$ 的邻项奇偶性不相同。

---

考虑到 $A$ 能被排序成严格单调的，这要求 $A$ 的元素互异，我们最后在答案中乘一个 $N!$ 即可。现在认为 $A$ 已经严格递增。

考虑取 $A$ 的差分序列 $D$，则邻项奇偶性不同转化为 $D$ 中每项都是奇数。最后考虑 $a_1$ 的取值，可以构造生成函数：

$$
\left(1 + x + x^2 + x^3 + \cdots\right) \left(x + x^3 + x^5 + \cdots\right)^{N - 1}
$$

其中 $1, x, x^2, \cdots, x^M$ 的系数之和即为所求。然而我们希望能够只求一个项的系数，考虑乘以 $1 / \left(1 - x\right) = 1 + x + x^2 + x^3 + \cdots$，则只需要求 $x^M$ 的系数即可：

$$
\begin{aligned}
&\left(1 + x + x^2 + x^3 + \cdots\right)^2 \left(x + x^3 + x^5 + \cdots\right)^{N - 1} \\
&= \frac{x^{N - 1}}{\left(1 - x\right)^2 \left(1 - x^2\right)^{N - 1}} = \frac{x^{N - 1}}{\left(1 - x\right)^{N + 1} \left(1 + x\right)^{N - 1}} \\
&= x^{N - 1} \left[\sum_{i = 0}^\infty \binom{i + N}{N} x^i\right] \left[\sum_{i = 0}^\infty \left(-1\right)^i\binom{i + N - 2}{N - 2} x^i\right]
\end{aligned}
$$

于是 $x^M$ 的系数为：

$$
\left[x^M\right] = \sum_{i = 0}^{M - N + 1} \left(-1\right)^i \binom{i + N - 2}{N - 2} \binom{M - i + 1}{N}
$$

时间复杂度 $O\left(\max\{N, M\}\right)$。注意 $N = 1$ 时的特殊处理。

---

```py
import math

P = 998244353

N, M = [int(_) for _ in input().split()]

fac = [1] * (M + 2)
for i in range(1, M + 2):
    fac[i] = fac[i - 1] * i % P

ifac = [1] * (M + 1) + [pow(fac[M + 1], P - 2, P)] * 1
for i in range(M + 1, 0, -1):
    ifac[i - 1] = ifac[i] * i % P

comb = lambda m, n: fac[m] * ifac[n] * ifac[m - n] % P if m >= n else 0

ans = 0
if N >= 2:
    for i in range(M - N + 2):
        ans += pow(-1, i, P) * comb(i + N - 2, N - 2) * comb(M - i + 1, N)
        ans %= P
else:
    ans = (M + 1) % P

print(ans * math.factorial(N) % P)
```

## E - Sequence 3

求满足如下条件的长度为 $N$ 的序列 $A = \left(a_1, a_2, \cdots, a_N\right)$ 的数量，对 $998244353$ 取模：

* $1 \le a_i \le M$；
* 对每个 $m$ 满足 $1 \le m \le M$，$m$ 在 $A$ 中出现的次数不超过 $m$。

---

考虑直接算每个 $m$ 出现了多少次，我们在每个 $x^i$ 上添加系数 $1 / i!$，将重复统计的 $i$ 删掉。

考虑构造生成函数：

$$
\prod_{i = 1}^M \sum_{j = 0}^i \frac{x^j}{j!} = \prod_{i = 1}^M \left(1 + x + \frac{x^2}{2!} + \cdots + \frac{x^i}{i!}\right)
$$

即求 $x^N$ 的系数。暴力进行 $O(M)$ 次多项式卷积即可，时间复杂度 $O(MN^2)$。

本题引入了指数生成函数。

---

```py
import math

P = 998244353

N, M = [int(_) for _ in input().split()]

ifac = [1] * (M + 1)
ifac[M] = pow(math.factorial(M), P - 2, P)
for i in range(M, 0, -1):
    ifac[i - 1] = ifac[i] * i % P

f = [1] + [0] * N
for i in range(1, M + 1):
    g = [0] * (N + 1)
    for j in range(0, N + 1):
        for k in range(0, j + 1):
            g[j] += f[k] * (ifac[j - k] if j - k <= i else 0) % P
            g[j] %= P
    f = g

print(f[N] * math.factorial(N) % P)
```

## F - Colored Paper

有排成一列的 $N$ 个格子，你要将每个格子染成红、蓝、黄三种颜色，且要求涂成蓝色的格子的个数为偶数，涂成黄色的格子的个数为奇数。求染色方案个数，对 $998244353$ 取模。两种染色方案不同，当且仅当存在某个格子在两个染色方案中染成不同颜色。

---

考虑枚举每种颜色染了多少个格子。对每种颜色，设当前染了 $k$ 个格子，则 $x^k$ 的系数为 $1 / k!$，可以去掉相同颜色的顺序。

构造如下若干生成函数：

$$
\begin{aligned}
R\left(x\right) &= 1 + x + \frac{x^2}{2!} + \frac{x^3}{3!} + \cdots \\
B\left(x\right) &= 1 + \frac{x^2}{2!} + \frac{x^4}{4!} \cdots \\
Y\left(x\right) &= x + \frac{x^3}{3!} + \frac{x^5}{5!} \cdots
\end{aligned}
$$

考虑 $\mathrm{e}^x$ 的 Taylor 展开式形如：

$$
\mathrm{e}^x = \sum_{i = 0}^\infty \frac{x^i}{i!} = 1 + x + \frac{x^2}{2!} + \frac{x^3}{3!} + \cdots
$$

于是 $R\left(x\right) = \mathrm{e}^x$。

下面考虑 $B\left(x\right), Y\left(x\right)$ 与 $R \left(x\right)$ 之间的联系。注意到：

$$
\begin{aligned}
B\left(x\right) + Y\left(x\right) &= 1 + x + \frac{x^2}{2!} + \frac{x^3}{3!} + \cdots &= R\left(x\right) \\
B\left(x\right) - Y\left(x\right) &= 1 - x + \frac{x^2}{2!} - \frac{x^3}{3!} + \cdots \\
&= 1 + (-x) + \frac{(-x)^2}{2!} + \frac{(-x)^3}{3!} + \cdots &= R\left(-x\right)
\end{aligned}
$$

于是：

$$
\begin{cases}
B \left(x\right) &= \frac{1}{2}\left[R\left(x\right) + R\left(-x\right)\right] = \frac{1}{2}\left(\mathrm{e}^x + \mathrm{e}^{-x}\right)\\
Y \left(x\right) &= \frac{1}{2}\left[R\left(x\right) - R\left(-x\right)\right] = \frac{1}{2}\left(\mathrm{e}^x - \mathrm{e}^{-x}\right) \\
\end{cases}
$$

最后，答案即为 $N! \cdot \left(R \left(x\right)B \left(x\right)Y \left(x\right) \left[x^N\right]\right)$，化简有：

$$
\begin{aligned}
R \left(x\right)B \left(x\right)Y \left(x\right) &= \frac{\mathrm{e}^x}{4}\left(\mathrm{e}^x + \mathrm{e}^{-x}\right)\left(\mathrm{e}^x - \mathrm{e}^{-x}\right) \\
&= \frac{\mathrm{e}^{3x} - \mathrm{e}^{-x}}{4}
\end{aligned}
$$

考虑前述展开式的推广：

$$
\mathrm{e}^{\alpha x} = \sum_{i = 0}^\infty \frac{\left(\alpha x\right)^i}{i!} = 1 + \alpha x + \frac{\left(\alpha x\right)^2}{2!} + \frac{\left(\alpha x\right)^3}{3!} + \cdots \iff \mathrm{e}^{\alpha x} \left[x^i\right] = \frac{\alpha^i}{i!}
$$

于是：

$$
\begin{aligned}
N! \cdot \left(R \left(x\right)B \left(x\right)Y \left(x\right) \left[x^N\right]\right) &= N! \left(\frac{\mathrm{e}^{3x} - \mathrm{e}^{-x}}{4} \left[x^N\right]\right) \\
&= N! \left(\frac{\mathrm{e}^{3x}\left[x^N\right]}{4} - \frac{\mathrm{e}^{-x}\left[x^N\right]}{4} \right) = N! \left(\frac{3^N}{4 \cdot N!} - \frac{(-1)^N}{4 \cdot N!}\right) \\
&= \frac{3^N - (-1)^N}{4}
\end{aligned}
$$

即为所求。时间复杂度 $O(\log N)$。

---

```py
P = 998244353

N = int(input())

print((pow(3, N, P) + pow(-1, N + 1, P)) * pow(4, P - 2, P) % P)
```

## G - Coin

你拥有面额为 $1, 2, \cdots, M$ 的硬币，每种面额的硬币都有无限种。

现在你只能用面额为 $m, m + 1, \cdots, m + L - 1$ 的硬币去凑出总金额 $N$，求使用硬币的方案数，对 $998244353$ 取模。两种方案不同，当且仅当存在某种面额的硬币用的个数不一样。

对每个 $m = 1, 2, \cdots, M - L + 1$，求出上述问题的答案。

---

对面额为 $k$ 的硬币，其对方案数的贡献可用以下生成函数表示：

$$
F_k \left(x\right) = 1 + x^k + x^{2k} + \cdots = \frac{1}{1 - x^k}
$$

那么对某个 $m$，考虑表示当前方案数的生成函数：

$$
G_m \left(x\right) = F_m \left(x\right) F_{m + 1} \left(x\right) \cdots F_{m + L - 1} \left(x\right)
$$

于是对这个 $m$ 的答案即为 $G_m \left(x\right) \left[x^N\right]$。考虑相邻 $G_m$ 的关系：

$$
G_{m + 1}\left(x\right) = G_m\left(x\right) \cdot \frac{F_{m + L}\left(x\right)}{F_m \left(x\right)}
$$

于是可以维护次数为 $N$ 的多项式 $G$，支持以下操作：

* 乘以 $1 - x^k$；
* 除以 $1 - x^k$，即乘以 $\left(1 + x^k + x^{2k} + \cdots\right)$。

两种操作分别可以转化成 01 背包问题和完全背包问题。第一种操作是比较显然的，第二种操作可以看成选多个重量为 $k$ 的物品，也就是完全背包问题。

利用不同的循环顺序即可在 $O(N)$ 时间内进行一次操作。而对相邻的 $m$ 要进行两次操作。

时间复杂度 $O(NM)$。本题体现了生成函数与背包问题之间的联系。

---

```py
P = 998244353

N, M, L = [int(_) for _ in input().split()]

f = [1] + [0] * N

for m in range(1, M + 1):
    for i in range(m, N + 1):
        f[i] += f[i - m]
        f[i] %= P
    
    if m >= L:
        print(f[N] % P)
        for i in range(N, m - L, -1):
            f[i] -= f[i - m + L - 1]
            f[i] %= P
```

## H - Jump

你站在 2D 平面的点 $(0, 0)$ 处，目标是到达 $(N, M)$。

你可以进行任意次（包括零次）操作，每次操作你可以选择两个自然数 $a, b$，使得 $0 \le a \le 1, 0 \le b$ 且 $(a, b) \neq (0, 0)$，假定你现在站在点 $(x, y)$ 处，则操作后你站在点 $(x + a, y + b)$ 处。

求到达 $(N, M)$ 的方案数，对 $998244353$ 取模。

---

考虑每次操作对坐标的贡献，可以用如下的二元生成函数表达：

$$
\begin{aligned}
F \left(x, y\right) &= \left(x^0 + x^1\right) \left(y^0 + y^1 + y^2 + \cdots\right) - x^0y^0 \\
&= \left(1 + x\right) \cdot \frac{1}{1 - y} - 1 = \frac{x + y}{1 - y}
\end{aligned}
$$

于是考虑总共用了若干操作次数的情况下对坐标的贡献：

$$
G \left(x, y\right) = \sum_{i = 0}^\infty \left[F \left(x, y\right)\right]^i
$$

$\left[x^N y^M\right] G \left(x, y\right)$ 即为答案。化简上式得：

$$
\begin{aligned}
G \left(x, y\right) &= \sum_{i = 0}^\infty \left[F \left(x, y\right)\right]^i \\
&= \frac{1}{1 - F \left(x, y\right)} = \frac{1}{1 - \frac{x + y}{1 - y}} \\
&= \frac{1 - y}{1 - x - 2y} = \frac{1}{1 - x - 2y} - \frac{y}{1 - x - 2y}
\end{aligned}
$$

于是：

$$
\begin{aligned}
\left[x^N y^M\right] G \left(x, y\right) &= \left[x^N y^M\right] \frac{1}{1 - x - 2y} - \left[x^N y^{M - 1}\right] \frac{1}{1 - x - 2y}
\end{aligned}
$$

计算目标项系数：

$$
\begin{aligned}
\left[x^N y^M\right] \frac{1}{1 - x - 2y} &= \left[x^N y^M\right] \frac{1}{1 - \left(x + 2y\right)} \\
&= \left[x^N y^M\right] \left[\underbrace{\left(x + 2y\right)^0 + \left(x + 2y\right)^1 + \cdots}_{\text{exp < N + M}} + \left(x + 2y\right)^{N + M} + \underbrace{\left(x + 2y\right)^{N + M + 1} + \cdots}_{\text{exp > N + M}}\right] \\
&= \left[x^N y^M\right] \left(x + 2y\right)^{N + M} = 2^{M} \binom{N + M}{N} 
\end{aligned}
$$

类似地：

$$
\left[x^N y^{M - 1}\right] \frac{1}{1 - x - 2y} = 2^{M - 1} \binom{N + M - 1}{N}
$$

于是答案即为：

$$
2^{M} \binom{N + M}{N} - 2^{M - 1} \binom{N + M - 1}{N}
$$

时间复杂度 $O(N + M)$。本题引入了二元生成函数。

本题也存在利用隔板法的简单组合数学做法。

---

```py
P = 998244353

def factorial(n: int):
    result = 1
    for i in range(1, n + 1):
        result *= i
        result %= P
    return result


N, M = [int(_) for _ in input().split()]

f0 = factorial(N + M) * pow(factorial(N), P - 2, P) * pow(factorial(M), P - 2, P) % P
f1 = factorial(N + M - 1) * pow(factorial(N), P - 2, P) * pow(factorial(M - 1), P - 2, P) % P

g0 = pow(2, M, P)
g1 = pow(2, M - 1, P)

print((f0 * g0 - f1 * g1) % P)
```

## NTT 的引入

后面的题目开始与快速数论变换相关了。本文假定读者已经掌握了 NTT 实现。

后文用到的 NTT 实现如下（模数为 $998244353$）：

```py
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
    Returns the convolution result modulo P.
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
```

## I - Score

你有 $N$ 个不同的数 $A_1, A_2, \cdots, A_N$。你将选择它们之中的 $K$ 个，定义得分为选出来的数的乘积，即假定选出数的集合为 $S$，则得分为 $\prod_{i \in S} i$。求所有方案的得分之和，对 $998244353$ 取模。

---

tbd

---

```py
P = 998244353
G = 3

def convolution(a: list[int], b: list[int]):
    ...

N, K = [int(_) for _ in input().split()]
A = [int(_) for _ in input().split()]

def derive(V: list[int]) -> list[int]:
    s = len(V)
    if s == 1:
        return [1, V[0]]
    return convolution(derive(V[ : s // 2]), derive(V[s // 2 : ]))

print(derive(A)[K])

```