#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <utility>

template <typename Value, typename Lazy>
class LazySegmentTree {
    int n;
    std::vector<Value> value;
    std::vector<Lazy> lazy;

    constexpr inline int ls(const int x) { return (x << 1) | 1; }
    constexpr inline int rs(const int x) { return (x + 1) << 1; }

    constexpr void push(const int x) {
        value[ls(x)] += lazy[x];
        value[rs(x)] += lazy[x];
        lazy[ls(x)] += lazy[x];
        lazy[rs(x)] += lazy[x];
        lazy[x] = Lazy();
    }

    constexpr void pull(const int x) {
        value[x] = value[ls(x)] + value[rs(x)];
    }

    void set(int x, int l, int r, const int L, const int R, const Lazy& K) {
        if (L <= l && r <= R) {
            value[x] += K;
            lazy[x] += K;
            return;
        }
        int m = (l + r) >> 1;
        push(x);
        if (L < m) {
            set(ls(x), l, m, L, R, K);
        }
        if (R > m) {
            set(rs(x), m, r, L, R, K);
        }
        pull(x);
    }

    Value get(int x, int l, int r, const int L, const int R) {
        if (L <= l && r <= R) {
            return value[x];
        }
        int m = (l + r) >> 1;
        push(x);
        if (R <= m) {
            return get(ls(x), l, m, L, R);
        }
        if (L >= m) {
            return get(rs(x), m, r, L, R);
        }
        return get(ls(x), l, m, L, R) + get(rs(x), m, r, L, R);
    }

public:
    void set(const int l, const int r, const Lazy& k) {
        if (l < r) {
            set(0, 0, n, l, r, k);
        }
    }
    Value get(const int l, const int r) {
        if (l < r) {
            return get(0, 0, n, l, r);
        } else {
            return Value();
        }
    }

    LazySegmentTree(const int n) : n(n), value(n << 2), lazy(n << 2) {
        std::vector<Value> init(n, Value());
        auto build = [&](auto& self, int x, int l, int r) -> void {
            if (r - l == 1) {
                value[x] = init[l];
                return;
            }
            int m = (l + r) >> 1;
            self(self, this->ls(x), l, m);
            self(self, this->rs(x), m, r);
            value[x] = value[this->ls(x)] + value[this->rs(x)];
        };

        build(build, 0, 0, n);
    }
};

struct Lazy {
    int add;
    Lazy(const int add = 0) : add(add) {}
    Lazy& operator+=(const Lazy& x) {
        add += x.add;
        return *this;
    }
};

struct Value {
    int sum, size;
    Value(const int sum = 0, const int size = 1) : sum(sum), size(size) {}
    Value& operator+=(const Lazy& x) {
        sum += x.add * size;
        return *this;
    }
};

Value operator+(const Value& x, const Value& y) {
    return Value(x.sum + y.sum, x.size + y.size);
}

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> vref(n);
    for (int i = 0; i < n; ++i) {
        vref[a[i]] = i;
    }

    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> id(n), ref(n), depth(n), size(n, 1), father(n, -1), heavy(n, -1), top(n);
    
    auto find_heavy = [&](auto& self, int cur, int par) -> void {
        for (const auto& to : adj[cur]) {
            if (to == par) {
                continue;
            }
            depth[to] = depth[cur] + 1;
            father[to] = cur;

            self(self, to, cur);

            size[cur] += size[to];
            if (!~heavy[cur] || size[to] > size[heavy[cur]]) {
                heavy[cur] = to;
            }
        }
    };

    auto find_top = [&, cnt = 0](auto& self, int cur, int fst) mutable -> void {
        top[cur] = fst;
        id[cur] = cnt;
        ref[cnt] = cur;
        ++cnt;

        if (!~heavy[cur]) {
            return;
        }

        self(self, heavy[cur], fst);
        for (const auto& to : adj[cur]) {
            if (to != father[cur] && to != heavy[cur]) {
                self(self, to, to);
            }
        }
    };

    find_heavy(find_heavy, 0, -1);
    find_top(find_top, 0, 0);

    LazySegmentTree<Value, Lazy> T(n);

    auto get_path = [&](int u, int v) {
        Value uside, vside;
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) {
                vside = vside + T.get(id[top[v]], id[v] + 1);
                v = father[top[v]];
            } else {
                uside = T.get(id[top[u]], id[u] + 1) + uside;
                u = father[top[u]];
            }
        }
        if (depth[u] < depth[v]) {
            return uside + T.get(id[u], id[v] + 1) + vside;
        } else {
            return vside + T.get(id[v], id[u] + 1) + uside;
        }
    };

    std::vector<std::pair<int, int>> q(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        q[i] = {u, v};
    }

    std::vector<int> ans(m);
    auto binary_search = [&](auto& self, int l, int r, const std::vector<int>& cand) -> void {
        if (r - l == 1) {
            for (const auto& i : cand) {
                ans[i] = l;
            }
            return;
        }

        int m = (l + r) >> 1;

        for (int i = m; i < r && i < n; ++i) {
            T.set(id[vref[i]], id[vref[i]] + 1, Lazy(-1));
        }

        std::vector<int> lhs, rhs;
        for (const auto& i : cand) {
            const auto& [u, v] = q[i];
            int sum = get_path(u, v).sum;
            if (sum == m) {
                rhs.push_back(i);
            } else {
                lhs.push_back(i);
            }
        }

        if (lhs.empty() == false) {
            self(self, l, m, lhs);
        }

        for (int i = m; i < r && i < n; ++i) {
            T.set(id[vref[i]], id[vref[i]] + 1, Lazy(1));
        }

        if (rhs.empty() == false) {
            self(self, m, r, rhs);
        }
    };

    T.set(0, n, Lazy(1));
    std::vector<int> all(m);
    std::iota(all.begin(), all.end(), 0);
    binary_search(binary_search, 0, n + 1, all);

    for (int i = 0; i < m; ++i) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}