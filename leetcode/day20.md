[Link](https://leetcode.cn/problems/minimum-operations-to-equalize-binary-string/)

给你一个二进制字符串 $s$ 和一个整数 $k$。

在一次操作中，你必须选择恰好 $k$ 个不同的下标，并将每个 $0$ 翻转为 $1$，每个 $1$ 翻转为 $0$。

返回使字符串中所有字符都等于 $1$ 所需的最少操作次数。如果不可能，则返回 $-1$。

如 $s = 0101, k = 3$，可以如此进行操作将 $s$ 变为 $1111$：

1. 翻转下标 $[0, 1, 3]$。$s$ 从 $0101$ 变为 $1000$。
2. 翻转下标 $[1, 2, 3]$。$s$ 从 $1000$ 变为 $1111$。

记 $n = \mathrm{len}(s)$，保证 $1 \le k \le n \le 10^5$，$s$ 只含有 $0, 1$。

---

## 矩阵建模

设一个合法的方案中进行了 $m$ 次操作，第 $i$ 次操作形如一个 $n$ 维（行）向量 $x_i$，其中每个元素 $x_{i,j}$ 为 $0$ 或 $1$，代表对第 $j$ 个位置不进行 / 进行一次翻转。

如上述例子可以写成 $2$ 个 $4$ 维向量（即 $2 \times 4$ 矩阵）：

$$
X = \begin{pmatrix}
1 & 1 & 0 & 1 \\
0 & 1 & 1 & 1 \\
\end{pmatrix}
$$

一般地，我们有 $01$ 矩阵 $X$，大小为 $m$ 行 $n$ 列。这代表对 $s$ 的一种操作集合。

## 必要条件

为了探索 $X$ 的性质，考虑刻画矩阵 $X$ 存在的必要条件。

### 核心条件

#### 行观点

任取 $0 \le i \le m - 1$，每次操作 $x_i$ 都恰好翻转了 $k$ 个位置。

**因此 $X$ 的每一行之和均为 $k$**，即任取 $i$ 都有：

$$
\sum_{j = 0}^{n - 1} X_{i,j} = k
$$

#### 列观点

任取 $0 \le j \le n - 1$，对 $s$ 的第 $j$ 个字符 $s_j$，

* 如果 $s_j = 0$，则 $j$ 这个位置必然经过奇数次操作。
**即 $X$ 的第 $j$ 列之和为奇数**。
$$
\left(\sum_{i = 0}^{m - 1} X_{i,j}\right) \bmod 2 = 1
$$

* 如果 $s_j = 1$，则 $j$ 这个位置必然经过偶数次操作。
**即 $X$ 的第 $j$ 列之和为偶数**。
$$
\left( \sum_{i = 0}^{m - 1} X_{i,j} \right) \bmod 2 = 0
$$

### 算两次思想与奇偶性判定

上面的讨论都关于矩阵 $X$ 的元素和 $\sum_i \sum_j X_{i, j}$，综合两个条件得到：

$$
\begin{aligned}
m \cdot k = \sum_{i = 0}^{m - 1} k &= \sum_{i = 0}^{m - 1} \left(\sum_{j = 0}^{n - 1} X_{i,j}\right) \\
&= \sum_{j = 0}^{n - 1} \left(\sum_{i = 0}^{m - 1} X_{i,j} \right) = \sum_{j = 0}^{n - 1} \left (2 \epsilon + \left[s_j = 0\right] \right) = 2 \epsilon + \sum_{j = 0}^{n - 1} \left[s_j = 0\right]
\end{aligned}
$$

上面的式子利用了**算两次**的思想，两行重合的部分交换了求和顺序。第一行是**先对行求和、再对列求和**，第二行是**先对列求和、再对行求和**。

第二行的 $\epsilon$ 是一些自然数。暂时忽略 $\epsilon$，等式两边对 $2$ 取模，有

$$
(m \cdot k) \bmod 2 = \left(\sum_{j = 0}^{n - 1} \left[s_j = 0\right]\right) \bmod 2
$$

注意到 $\sum_{j} \left[s_j = 0\right]$ 即为 $s$ 中 $0$ 的个数，记为 $c$。式子化为：

$$
\boxed{
(m \cdot k) \bmod 2 = c \bmod 2
}
$$

### 应用极端原理

现在考虑利用极端原理：矩阵 $X$ 元素和 $m \cdot k$ 的极值是多少？

#### 下界

最好情况下，我们只需要把每个 $s_j = 0$ 的位置翻转一次，剩下的 $s_j = 1$ 的位置不需要翻转。因此：

$$
m \cdot k = \sum_i \sum_j X_{i,j} \ge 1 \cdot c + 0 \cdot (n - c) = c
$$

#### 上界

最坏情况下，每个位置都反复被翻转了。这里分 $m$ 的奇偶性讨论：

##### $m$ 为奇数

* $s_j = 0$ 的位置翻转了 $m$ 次，
* $s_j = 1$ 的位置翻转了 $m - 1$ 次。

$$\sum_i \sum_j X_{i,j} \le m \cdot c + (m - 1) \cdot (n - c) = m \cdot n - (n - c)$$

##### $m$ 为偶数

* $s_j = 0$ 的位置翻转了 $m - 1$ 次，
* $s_j = 1$ 的位置翻转了 $m$ 次。

$$\sum_i \sum_j X_{i,j} \le (m - 1) \cdot c + m \cdot (n - c) = m \cdot n - c$$

### 结论

综上所述，我们得到了若干必要条件：

* $(m \cdot k) \bmod 2 = c \bmod 2$
* 若 $m$ 为奇数，
$$
c \le mk \le mn - (n - c)
$$
* 若 $m$ 为偶数，
$$
c \le mk \le mn - c
$$

## 充分性证明

事实上上述必要条件也是充分的。下面说明其充分性，即只要 $m$ 满足这样的条件，必然存在对应的合法的 $X$。

### 初始条件 $X_0$

取一个矩阵 $X_0$，使得对任意的 $0 \le j \le n - 1$，只要 $s_j = 0$，那么第 $j$ 行恰有一个 $1$（即和为 $1$），否则全为 $0$；并且每一列的元素和均不超过 $k$。

此时矩阵 $X_0$ 元素和为 $c \le mk$，必然存在一种方案使得每列合法（考虑对有 $1$ 的行构成的子矩阵，沿着循环意义下的对角线填 $1$，即为合法方案）。

### 调整变换

一个重要的观察是：每次选择 $0 \le i_1, i_2 \le n - 1$ 且 $i_1 \neq i_2$，令 $X_{i_1, j}, X_{i_2, j}$ 翻转，不会影响最终的串 $s$。即对两次操作，如果都没有翻转某个位置，则同时翻转这个位置效果不变。

于是一直对 $X_0$ 做这样的变换，每次会使得 $X_0$ 的元素和变大 $2$。每一行进行这样的变换次数是有限的，最后一定会让一行变成全 $1$ 或仅剩下一个 $0$，也就是有 $m$ 个 $1$ 或 $m - 1$ 个 $1$（取决于 $s_j$ 和 $m$ 的奇偶性），对应最大值。

### 应用介值定理

考虑条件 $c \le mk \le mn - \Delta = \max$，并且 $mk \bmod 2 = c \bmod 2$，由离散介值定理可知过程中元素和能够取到 $mk$。

另外，过程中也不会存在某些列，其一列的元素和不等于 $k$。

只需保证我们每次选择时都选择元素和最小的列，结束时若存在某些列，其一列的元素和小于 $k$，说明先前有操作未选择最小的列来加，这导致矛盾；若不存在，则根据同向不等式可加性可说明每列的元素和均为 $k$。

## 构造最小值作为答案

充分性证毕，下面说明如何求答案。整理不等式条件 $c \le mk \le mn - \Delta = \max$，分奇偶讨论：

### $m$ 是奇数

令 $m = 2u - 1$，其中 $u$ 是整数。

$$
\begin{aligned}
c \le (2u - 1) k \iff &u \ge \left \lceil \frac{c + k}{2k} \right \rceil \\
(2u - 1) k \le (2u - 1)n - (n - c) \iff &u \ge \left \lceil \frac{2n - c - k}{2(n - k)} \right \rceil \\
\end{aligned}
$$

注意 $c, k \le n$。因此最小奇数解 $m_{odd}$ 满足：

$$
\boxed{
    m_{odd} = 2 \cdot \min\left( \left \lceil \frac{c + k}{2k} \right \rceil, \left \lceil \frac{2n - c - k}{2(n - k)} \right \rceil\right) - 1}
$$

### $m$ 是偶数

令 $m = 2u$，其中 $u$ 是整数。

$$
\begin{aligned}
c \le 2u k \iff &u \ge \left \lceil \frac{c}{2k} \right \rceil \\
2uk \le 2un - c \iff &u \ge \left \lceil \frac{c}{2(n - k)} \right \rceil \\
\end{aligned}
$$

注意 $c, k \le n$。因此最小偶数解 $m_{even}$ 满足：

$$
\boxed{
m_{even} = 2 \cdot \min\left( \left \lceil \frac{c}{2k} \right \rceil, \left \lceil \frac{c}{2(n - k)} \right \rceil\right)
}
$$

验证 $m_{odd}$ 和 $m_{even}$ 是否满足充要条件即可。

## 复杂度分析

* 时间复杂度为 $O(n)$，瓶颈在于计算 $c$。
* 空间复杂度为 $O(n)$，瓶颈在于储存 $s$。

## 加强

本题可加强为给定 $n, c, k$，求答案，其中 $1 \le k \le n \le 10^9, 0 \le c \le n$。

加强实现难度，考虑构造一个操作序列。

---

```cpp
class Solution {
public:
    int uppdiv(int x, int y) { return (x + y - 1) / y; }
    int minOperations(std::string s, int k) {
        int n = s.size();
        int c = std::count(s.begin(), s.end(), '0');
        if (k == n) {
            return c == n ? 1 : -1;
        }
        int me = std::max(uppdiv(c, 2 * k), uppdiv(c, 2 * (n - k))) * 2;
        int mo = std::max(uppdiv(c + k, 2 * k), uppdiv(2 * n - c - k, 2 * (n - k))) * 2 - 1;
        int ans = INT_MAX;
        if (1LL * me * k % 2 == c % 2 && 1LL * me * n - c >= 1LL * me * k) {
            ans = std::min(me, ans);
        }
        if (1LL * mo * k % 2 == c % 2 && 1LL * mo * n - n + c >= 1LL * mo * k) {
            ans = std::min(mo, ans);
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

```