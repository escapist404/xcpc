给你两个整数 $\mathrm{left}$ 和 $\mathrm{right}$ ，在闭区间 $[\mathrm{left}, \mathrm{right}]$ 范围内，统计并返回**计算置位位数为质数**的整数个数。

**计算置位位数**就是二进制表示中 $1$ 的个数。

例如，$21$ 的二进制表示 $10101$ 有 $3$ 个计算置位。

保证 $1 \le \mathrm{left} \le \mathrm{right} \le 10^6, 0 \le \mathrm{right} - \mathrm{left} \le 10^4$

---

考虑到 $\mathrm{left}, \mathrm{right}$ 和 $\mathrm{right} - \mathrm{left}$ 都很小，我们可以直接遍历这些数并判断其是否满足条件。

对每个数 $i$，其计算置位位数至多为 $\lceil \log_2{i} \rceil \le 20$，因此我们只考虑不超过 $20$ 的质数即可。

预处理出这些质数（即 $2, 3, 5, 7, 11, 13, 17$），维护 `bool is[]` 仅在上述下标为 `true`，其余均为 `false`，遍历 `i` 时仅当 `is[__builtin_popcount(i)]` 为 `true` 时令 `ans++`。

或许你觉得要存下 $21$ 个数的内存还是太奢侈，事实上 `bool` 值可以用一个 bit 储存。考虑令

$$
\mathrm{is} = \left( 1010 \space 0010 \space 1000 \space 1010 \space 1100 \right)_2 = \left( \mathrm{A28AC} \right)_{16}
$$

仅在第 $2, 3, 5, 7, 11, 13, 17$ 位为 $1$。取 `1 << popcount(i) & is`，答案不为 `0` 即代表质数。

时间复杂度为 $O(\mathrm{right} - \mathrm{left})$，空间复杂度为 $O(1)$。

```cpp
class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        return std::ranges::count_if(std::views::iota(left, right + 1), [](const auto x) { return 1 << __builtin_popcount(x) & 0XA28AC; });
    }
};
```
