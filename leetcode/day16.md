给你一个二进制字符串 $s$ 和一个整数 $k$ 。如果所有长度为 $k$ 的二进制字符串都是 $s$ 的子串，请返回 `true` ，否则请返回 `false`。

保证 $1 \le \mathrm{len}(s) \le 5 \times 10^5, 1 \le k \le 20$

---

维护关于所有长度为 $k$ 的二进制串的桶，枚举 $s$ 的所有长度为 $k$ 的子串，并把每个子串放入桶中，最后统计各子串是否均出现了至少一次。

实现上不需要使用 `std::string` 储存长度为 $k$ 的串，可以直接用 `int` 代替。

时间复杂度 $O(n)$，空间复杂度 $O(2^k)$。

```cpp
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int n = s.size();
        std::vector<int> vis(1 << k);
        const int b = (1 << k) - 1;
        int t = 0;
        for (int i = 0; i < n; ++i) {
            t = (t << 1 ^ (s[i] == '1')) & b;
            if (i >= k - 1) {
                vis[t] = 1;
            }
        }
        return std::count(vis.begin(), vis.end(), 1) == 1 << k;
    }
};

```
