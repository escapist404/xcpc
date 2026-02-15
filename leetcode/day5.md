[Link](https://leetcode.cn/problems/longest-balanced-substring-i/)

给你一个由小写英文字母组成的字符串 $s$。

如果一个子串中所有**不同**字符出现的次数都相同 ，则称该子串为平衡子串。

请返回 $s$ 的最长平衡子串的长度。

子串是字符串中连续的、非空的字符序列。

保证字符串的长度不超过 $1000$，且仅由小写英文字母构成。

---

由于长度很小，我们依旧可以枚举每个子串，并判断其是否是平衡的。

具体地，对每个左端点 $i$ 固定的子串，维护一个关于字符的桶，逐个枚举右端点 $j$，在扩展右端点时记录某种字符的出现次数。

仅当桶中非零值均相同时，当前子串是平衡子串。为了快速维护这点，同时维护桶内最大值 $m$ 和非零值个数 $c$，仅当 $c \times m = j - i + 1$ 时，子串平衡。

以上，我们以 $O(n \Sigma + n^2)$ 的时间复杂度、$O(n + \Sigma)$ 的空间复杂度解决了本题。

---

[AC Link](https://leetcode.cn/problems/longest-balanced-substring-i/submissions/?envType=daily-question&envId=2026-02-12)

```cpp
class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            vector<int> c(26);
            int v = 0, p = 0, t = 0;
            for (int j = i; j < n; ++j) {
                if (c[s[j] - 'a'] == 0) {
                    t++;
                }
                c[s[j] - 'a']++;
                v = max(v, c[s[j] - 'a']);
                p++;
                if (p == t * v) {
                    ans = max(ans, j - i + 1);
                }
            }
        }
        return ans;
    }
};
```
