给定一个字符串 $s$，统计并返回具有相同数量 $0$ 和 $1$ 的非空（连续）子字符串的数量，并且这些子字符串中的所有 $0$ 和所有 $1$ 都是成组连续的。

重复出现（不同位置）的子串也要统计它们出现的次数。

---

注意到这样的子串关于 0 和 1 交界对称。在原串中求出每个极长连续串的长度，对两个相邻的极长连续串，对答案的贡献为两个串长度的较小值。

时间复杂度和空间复杂度均为 $O(n)$。

```cpp
class Solution {
public:
    int countBinarySubstrings(string s) {
        s = "?" + s + "?";
        int lst = 0, cur = 0, ans = 0;
        for (int i = 1; i < (int)s.size(); ++i) {
            if (s[i] == s[i - 1]) {
                cur++;
            } else {
                ans += min(lst, cur);
                lst = cur;
                cur = 1;
            }
        }
        return ans;
    }
};
```
