给你一个整数数组 $a$。

如果子数组中不同偶数的数量等于不同奇数的数量，则称该子数组是平衡的。

返回最长平衡子数组的长度。

子数组是数组中连续且非空的一段元素序列。

保证 $a$ 的长度不超过 $\mathbf{100000}$，数组中元素都是不超过 $100000$ 的正整数。

---

现在，$O(n^2)$ 的时间不可接受。固定右端点，思考如何快速找到最远左端点。

处理本质不同的数的个数，在固定端点后的一个常见的操作是，找到某个数出现的最后位置，加上记号。

即维护一个长度为 $n$ 的序列 $d$，在右端点 $i$ 遍历时，记 $l_v$ 为此时值 $v$ 在 $a$ 中最后一次出现的位置，则 $d_{l_{a_i}} \gets d_{l_{a_i}} - 1, d_{i} \gets d_{a_i} + 1, l_{a_i} \gets i$。这时对 $[k, i]$ 计算 $\sum d_j$，即为不同的数的个数。

考虑怎么构造偶数数量与奇数数量相同的条件，只需让奇数对 $d_i$ 的贡献为 $1$，偶数对 $d_i$ 的贡献为 $-1$，最后某个区间 $\sum d_j = 0$ 即认为不同的偶数个数与奇数个数相同。

现在右端点固定为 $i$，考虑怎么找最小的 $j$ 使得 $\sum_{k = j}^i d_k = 0$。发现这是一个形似后缀和的式子，记 $s_j = \sum_{k = j}^i d_k = 0$，只需找最小的 $s_j = 0$。

考虑使用线段树维护 $s_i$。每次改变 $d_i$ 时，相当于给 $[l_{a_i}, i]$ 这个区间上的 $s_i$ 加上 $1$ 或 $-1$，这能够用线段树方便地维护。

具体地，维护最大值和最小值。由于 $d_i \in \{-1, 0, 1\}$，根据离散介值定理，一个区间内 $s_i = \sum d_i$ 的值域取遍最小值与最大值之间的所有数。只需最大值非负，最小值非正，必有某个 $s_i = 0$ 存在。

于是变成找最小的 $j$，使得：

* $\max_{k = 0}^j s_k \ge 0$
* $\min_{k = 0}^j s_k \le 0$

或者变成找最大的 $k$，使得：

* $\max_{p = 0}^k s_p < 0$ 或 $\min_{p = 0}^k s_p > 0$

这里 $j = k + 1$。

这些都可以用线段树上二分的技巧在 $O(\log n)$ 的时间内解决。至此，本题可以在 $O(n \log n)$ 的时间、$O(n + V)$ 的空间下解决。

```cpp
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        const int V = 1E5;
        const int INF = 1E9;
        int n = nums.size();

        using Info = std::pair<int, int>;
        using Lazy = int;

        auto e = [INF]() {
            return Info(-INF, INF);
        };

        auto op = [](const Info& x, const Info& y) {
            return Info(max(x.first, y.first), min(x.second, y.second));
        };

        auto mapping = [](const Lazy& x, const Info& y) {
            return Info(y.first + x, y.second + x);
        };

        auto composition = [](const Lazy& x, const Lazy& y) {
            return x + y;
        };

        auto idl = []() {
            return 0;
        };

        std::vector<Info> info(4 * n);
        std::vector<Lazy> lazy(4 * n);

        auto push = [&](const int id) {
            info[2 * id + 1] = mapping(lazy[id], info[2 * id + 1]);
            info[2 * id + 2] = mapping(lazy[id], info[2 * id + 2]);
            lazy[2 * id + 1] = composition(lazy[id], lazy[2 * id + 1]);
            lazy[2 * id + 2] = composition(lazy[id], lazy[2 * id + 2]);
            lazy[id] = idl();
        };

        auto pull = [&](const int id) {
            info[id] = op(info[2 * id + 1], info[2 * id + 2]);
        };

        auto set = [&](const int L, const int R, const Lazy& K) {
            auto _set = [&](auto& self, int id, int l, int r) {
                if (L <= l && r <= R) {
                    info[id] = mapping(K, info[id]);
                    lazy[id] = composition(K, lazy[id]);
                    return;
                }
                push(id);
                int m = l + (r - l) / 2;
                if (m > L) {
                    self(self, 2 * id + 1, l, m);
                }
                if (m < R) {
                    self(self, 2 * id + 2, m, r);
                }
                pull(id);
            };
            return _set(_set, 0, 0, n);
        };

        auto get = [&](const int L, const int R) {
            auto _get = [&](auto& self, int id, int l, int r) {
                if (L <= l && r <= R) {
                    return info[id];
                }
                push(id);
                int m = l + (r - l) / 2;
                if (m >= R) {
                    return self(self, 2 * id + 1, l, m);
                }
                if (m <= L) {
                    return self(self, 2 * id + 2, m, r);
                }
                return op(self(self, 2 * id + 1, l, m), self(self, 2 * id + 2, m, r));
            };
            return _get(_get, 0, 0, n);
        };

        auto min_left = [&](const int R, auto P) {
            if (R == 0) {
                return 0;
            }
            Info i = Info();
            auto _min_left = [&](auto& self, int id, int l, int r) {
                if (r <= R) {
                    Info ii = op(info[id], i);
                    if (P(ii)) {
                        i = ii;
                        return l;
                    }
                    if (l + 1 == r) {
                        return r;
                    }
                }
                push(id);
                int m = l + (r - l) / 2;
                if (R > m) {
                    int ret = self(self, 2 * id + 2, m, r);
                    if (ret > m) {
                        return ret;
                    }
                }
                return self(self, 2 * id + 1, l, m);
            };
            return _min_left(_min_left, 0, 0, n);
        };

        auto max_right = [&](const int L, auto P) {
            if (L == n) {
                return n;
            }
            Info i = e();
            auto _max_right = [&](auto& self, int id, int l, int r) {
                if (l >= L) {
                    Info ii = op(i, info[id]);
                    if (P(ii)) {
                        i = ii;
                        return r;
                    }
                    if (l + 1 == r) {
                        return l;
                    }
                }
                push(id);
                int m = l + (r - l) / 2;
                if (L < m) {
                    int ret = self(self, 2 * id + 1, l, m);
                    if (ret < m) {
                        return ret;
                    }
                }
                return self(self, 2 * id + 2, m, r);
            };
            return _max_right(_max_right, 0, 0, n);
        };

        std::vector<int> lst(V + 1, 0);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int v = nums[i] % 2 == 1 ? 1 : -1;
            set(lst[nums[i]], i + 1, Lazy(v));
            lst[nums[i]] = i + 1;
            int r = max_right(0, [](const Info& x) {
                return x.first < 0 || x.second > 0;
            });
            ans = max(ans, i + 1 - r);
        }

        return ans;
    }
};
```
