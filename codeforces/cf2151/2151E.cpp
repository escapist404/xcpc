#include <bits/stdc++.h>

template <typename V, typename T>
class LazySegmentTree {
    int n;
    std::vector<V> val;
    std::vector<T> tag;
 
    constexpr int ls(const int id) const {
        return (id << 1) | 1;
    }
    constexpr int rs(const int id) const {
        return (id + 1) << 1;
    }
 
    void push(const int id) {
        val[ls(id)] += tag[id];
        val[rs(id)] += tag[id];
        tag[ls(id)] += tag[id];
        tag[rs(id)] += tag[id];
        tag[id] = T();
    }
 
    void pull(const int id) {
        val[id] = val[ls(id)] + val[rs(id)];
    }
 
    V get(const int l, const int r, const int id, const int cl, const int cr) {
        if (l <= cl && cr <= r) {
            return val[id];
        }
        push(id);
        int cm = (cl + cr) >> 1;
        if (r <= cm) {
            return get(l, r, ls(id), cl, cm);
        }
        if (l >= cm) {
            return get(l, r, rs(id), cm, cr);
        }
        return get(l, r, ls(id), cl, cm) + get(l, r, rs(id), cm, cr);
    }
 
    void set(const T& t, const int l, const int r, const int id, const int cl, const int cr) {
        if (l <= cl && cr <= r) {
            val[id] += t;
            tag[id] += t;
            return;
        }
        push(id);
        int cm = (cl + cr) >> 1;
        if (l < cm) {
            set(t, l, r, ls(id), cl, cm);
        }
        if (r > cm) {
            set(t, l, r, rs(id), cm, cr);
        }
        pull(id);
    }
 
public:
    V get(const int l, const int r) {
        if (r - l >= 1) {
            return get(l, r, 0, 0, n);
        } else {
            return V();
        }
    }
    void set(const T& t, const int l, const int r) {
        if (r - l >= 1) {
            set(t, l, r, 0, 0, n);
        }
    }
 
    LazySegmentTree(const std::vector<V>& v) : n(v.size()), val(n << 2), tag(n << 2) {
        auto build = [&](auto& self, const int id, const int cl, const int cr) {
            if (cr - cl == 1) {
                val[id] = v[cl];
                return;
            }
            int cm = (cl + cr) >> 1;
            self(self, ls(id), cl, cm);
            self(self, rs(id), cm, cr);
            pull(id);
        };
        build(build, 0, 0, n);
    }
};

using i64 = long long;
const i64 INF = 200'000'000'000'000LL;

struct Tag {
    i64 add;
    Tag(const i64 add = 0) : add(add) {}
    Tag& operator+=(const Tag& x) {
        add += x.add;
        return *this;
    }
};

struct Value {
    i64 max;
    Value(const i64 max = -INF) : max(max) {}
    Value& operator+=(const Tag& x) {
        max += x.add;
        return *this;
    }
};

Value operator+(const Value& x, const Value& y) {
    return Value(std::max(x.max, y.max));
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> v(n), r(n);
    {
        for (int i = 0; i < n; ++i) {
            std::cin >> v[i];
        }
        std::vector<int> map(n);
        for (int i = 0; i < n; ++i) {
            int x;
            std::cin >> x;
            --x;
            map[x] = i;
        }
        for (int i = 0; i < n; ++i) {
            int x;
            std::cin >> x;
            --x;
            r[map[x]] = i;
        }
        std::vector<int> tmp(n);
        for (int i = 0; i < n; ++i) {
            tmp[map[i]] = v[i];
        }
        v = tmp;
    }

    LazySegmentTree<Value, Tag> T(std::vector<Value>(n + 1));
    T.set({-T.get(0, 1).max}, 0, 1);

    for (int i = 0; i < n; ++i) {
        auto max = T.get(0, r[i] + 1).max;
        auto diff = max - T.get(r[i] + 1, r[i] + 2).max;
        T.set({std::max(diff, 0LL)}, r[i] + 1, r[i] + 2);
        T.set(v[i], 0, r[i] + 1);
    }

    std::cout << T.get(0, n + 1).max << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
