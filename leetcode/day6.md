给你一个只包含字符 `a`、`b` 和 `c` 的字符串 $s$。

如果一个子串中所有不同字符出现的次数都相同，则称该子串为平衡子串。

请返回 $s$ 的最长平衡子串的长度。

子串是字符串中连续的、非空的字符序列。

---

[AC Link](https://leetcode.cn/problems/longest-balanced-substring-ii/submissions/698492780/)

对每个平衡子串：

* 包含一种字符。最长的平衡子串贡献来源于极长的单一字符串。如 `aaabbbbbcccc` 中极长的单一字符串为 `aaa`、`bbbbb`、`cccc`。

用单次 `for` 循环维护极长的子串长度，遇到不同的串则把长度清空。每次更新后取最大值。

* 包含两种字符。将第三种字符作为分隔符，处理在每个分隔符之间的串。利用子串与到左右端点前缀的关系，维护两种字符在前缀的出现次数之差，只要差相同，即代表在这个区间内两种字符出现次数相同。记录这个差对应的第一个下标，每次再遇到这个差，都用当前的下标和第一个下标取长度。

用 `std::map` 分别存出现 `b - a`、`c - b`、`a - c` 的最早下标。遇到第三种字符就置为初始状态。需要注意边界问题：前缀为空时出现次数之差为零，这个需要存进去。

* 包含三种字符。依旧利用每个前缀字符出现次数之差，维护 `b - a` 和 `c - a` 的次数。每次出现 `a` 就让两个次数减一，出现 `b` 和 `c` 就让对应的次数加一。

用 `std::pair` 储存。每个这样的 `std::pair` 对应一个最早的下标，可以用 `std::map<std::pair<int, int>, int>` 维护。

时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$。

---

```cpp
class Solution {
public:
    int longestBalanced(string s) {
        int ans = 0;
        int n = s.size();
        {
            map<pair<int, int>, int> first;
            int b = 0, c = 0;
            first[make_pair(0, 0)] = -1;
            for (int i = 0; i < n; ++i) {
                if (s[i] == 'a') {
                    --b, --c;
                } else if (s[i] == 'b') {
                    ++b;
                } else {
                    ++c;
                }
                if (first.contains(make_pair(b, c))) {
                    ans = max(ans, i - first[make_pair(b, c)]);
                } else {
                    first[make_pair(b, c)] = i;
                }
            }
        }
        {
            map<int, int> first_ab, first_bc, first_ca;
            first_ab[0] = -1;
            first_bc[0] = -1;
            first_ca[0] = -1;
            int ab = 0, bc = 0, ca = 0;
            for (int i = 0; i < n; ++i) {
                if (s[i] == 'a') {
                    bc = 0;
                    first_bc.clear();
                    first_bc[0] = i;
                    ab--;
                    if (first_ab.contains(ab) == false) {
                        first_ab[ab] = i;
                    }
                    ca++;
                    if (first_ca.contains(ca) == false) {
                        first_ca[ca] = i;
                    }
                    ans = max({ans, i - first_ab[ab], i - first_ca[ca]});
                }
                if (s[i] == 'b') {
                    ca = 0;
                    first_ca.clear();
                    first_ca[0] = i;
                    ab++;
                    if (first_ab.contains(ab) == false) {
                        first_ab[ab] = i;
                    }
                    bc--;
                    if (first_bc.contains(bc) == false) {
                        first_bc[bc] = i;
                    }
                    ans = max({ans, i - first_ab[ab], i - first_bc[bc]});
                }
                if (s[i] == 'c') {
                    ab = 0;
                    first_ab.clear();
                    first_ab[0] = i;
                    bc++;
                    if (first_bc.contains(bc) == false) {
                        first_bc[bc] = i;
                    }
                    ca--;
                    if (first_ca.contains(ca) == false) {
                        first_ca[ca] = i;
                    }
                    ans = max({ans, i - first_bc[bc], i - first_ca[ca]});
                }
            }
        }
        {
            int a = 0, b = 0, c = 0;
            for (int i = 0; i < n; ++i) {
                if (s[i] == 'a') {
                    a++;
                    b = 0;
                    c = 0;
                }
                if (s[i] == 'b') {
                    b++;
                    c = 0;
                    a = 0;
                }
                if (s[i] == 'c') {
                    c++;
                    a = 0;
                    b = 0;
                }
                ans = max({ans, a, b, c});
            }
        }
        return ans;
    }
};
```
