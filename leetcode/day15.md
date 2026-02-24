[Link](https://leetcode.cn/problems/binary-gap/)

给定一个正整数 $n$，找到并返回 $n$ 的二进制表示中两个相邻 $1$ 之间的最长距离。如果不存在两个相邻的 $1$，返回 `0` 。

如果只有 $0$ 将两个 $1$ 分隔开（可能不存在 $0$），则认为这两个 $1$ 彼此相邻。两个 $1$ 之间的距离是它们的二进制表示中位置的绝对差。例如，$1001$ 中的两个 $1$ 的距离为 $3$。

---

利用位运算计算答案。利用补码为反码加一的特性，我们可以求出一个数 $n$ 的二进制最低置位 $\mathrm{lowbit}(n) = n \& -n$。每次减掉 $\mathrm{lowbit}(n)$，可以得到每一个置位。

令变量 $r$ 为最近的 $\mathrm{lowbit}$，答案为 $\log_2 \max (\mathrm{lowbit}(n) / r)$。令 $\mathrm{ans}$ 为里面的比率，初始时置其为 $1$。

时间复杂度为 $O(\log n)$，空间复杂度为 $O(1)$。

```cpp
class Solution {
public:
    int binaryGap(int n) {
        int r = 0;
        int ans = 1;
        while (n) {
            int s = n & -n;
            if (r) {
                ans = std::max(ans, s / r);
            }
            r = s;
            n -= s;
        }
        return std::__lg(ans);
    }
};

```
