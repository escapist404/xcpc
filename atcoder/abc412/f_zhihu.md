# AT_abc412_f Socks 4

[题目链接](https://atcoder.jp/contests/abc412/tasks/abc412_f)

在高桥的抽屉柜里，有 $$N$$ 种颜色的袜子，第 $$i$$ 种颜色的袜子有 $$A_i$$ 只。

开始时，高桥在柜子外放了一只第 $$C$$ 种颜色的袜子（与柜子里的袜子无关），然后执行下面的操作：

* 等概率地从柜子里抽出一只袜子。如果在柜子外面的两只袜子颜色相同，就结束操作。如果不同，选择一只袜子放回柜子里，且使得未来抽出袜子次数的期望最小。

求抽出袜子次数的期望，对 $$998244353$$ 取模。

---

考虑如何使得期望最小，只需要每次都保留数量更多的颜色对应的袜子，即保留 $$A_i$$ 更大的袜子。这样更有可能抽到相同的袜子。

于是在柜子外袜子对应的 $$A_i$$ 是单调不减的，这一点可以用来进行 dp。

令 $$A_C \gets A_C + 1$$，将 $$A_i$$ 从小到大排序，即 $$A_1 \le A_2 \le \cdots \le A_N$$，并且调整对应的 $$C$$。记在柜子里的袜子数量为 $$S = \left(\sum_{i = 1}^N A_i\right) - 1$$。

记 $$f_i$$ 代表柜子外袜子颜色为 $$i$$ 时，接下来抽出袜子次数的期望。假设抽到了一只颜色为 $$j$$ 的袜子，分类讨论转移如下：

* $$j < i$$
    排序后有 $$A_j \le A_i$$，保留原来的袜子，即：
    $$
    f_i \gets \frac{A_j}{S} \left(f_i + 1\right)
    $$
* $$j > i$$
    排序后有 $$A_i \le A_j$$，保留新抽到的袜子，即：
    $$
    f_i \gets \frac{A_j}{S} \left(f_j + 1\right)
    $$
* $$j = i$$
    达到终止条件，结束，即：
    $$
    f_i \gets \frac{A_i - 1}{S} \cdot 1
    $$
    式中 $$A_i - 1$$ 意味着柜子里剩下 $$A_i - 1$$ 只袜子。

合并有：

$$
\begin{aligned}
f_i &= \sum_{j = 1} ^ {i - 1} \frac{A_j}{S} \left(f_i + 1\right) + \sum_{j = i + 1} ^ N \frac{A_j}{S} \left(f_j + 1\right) + \frac{A_i - 1}{S} \cdot 1 \\
f_i &= \frac{1}{S} \left(\sum_{j = 1} ^ {i - 1} A_j \right) f_i + \frac{1}{S} \sum_{j = i + 1} ^ N \left(A_j \cdot f_j \right) + \frac{\left(\sum_{j = 1} ^ N A_j \right) - 1}{S} \\
\end{aligned}
$$

根据定义有 $$\frac{\left(\sum_{j = 1} ^ N A_j \right) - 1}{S} = 1$$。

$$
\begin{aligned}
\frac{S - \sum_{j = 1} ^ {i - 1} A_j}{S} f_i &= \frac{1}{S} \sum_{j = i + 1} ^ N \left(A_j \cdot f_j \right) + 1 \\
f_i &= \frac{\sum_{j = i + 1} ^ N \left(A_j \cdot f_j \right) + S}{S - \sum_{j = 1} ^ {i - 1} A_j}
\end{aligned}
$$

即为转移式，朴素地计算是 $$O(N ^ 2 \cdot \log P)$$ 的。发现 $$\sum_{j = i + 1} ^ N \left(A_j \cdot f_j \right)$$ 和 $$\sum_{j = 1} ^ {i - 1} A_j$$ 可以用前缀和优化，于是该问题在 $$O(N \log P)$$ 的时间内得到解决。

---

```py
P = 998244353

N, C = [int(i) for i in input().split()]
A = [int(i) for i in input().split()]

inverse = lambda base: pow(base, P - 2, P)

A[C - 1] += 1
ref = A[C - 1]
A = sorted(A)
S = sum(A) - 1

U, V = 0, S + 1

for i in reversed(range(N)):
    V -= A[i]
    f = (U + S) * inverse(S - V) % P
    U += A[i] * f
    if A[i] == ref:
        print(f)
        break

```