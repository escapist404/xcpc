#include <bits/stdc++.h>

#ifndef LAZYSEGTREE_HPP
#define LAZYSEGTREE_HPP

#include <type_traits>
#include <vector>

#if __cplusplus >= 201703L

template <typename V,
          auto op,
          auto e,
          typename L,
          auto mapping,
          auto composition,
          auto id>
class LazySegmentTree {
    static_assert(std::is_convertible_v<decltype(op), std::function<V(V, V)>>,
                  "op() must work as V(V, V)");
    static_assert(std::is_convertible_v<decltype(e), std::function<V()>>,
                  "e() must work as V()");
    static_assert(std::is_convertible_v<decltype(mapping), std::function<V(L, V)>>,
                  "mapping() must work as V(L, V)");
    static_assert(std::is_convertible_v<decltype(composition), std::function<L(L, L)>>,
                  "composition() must work as L(L, L)");
    static_assert(std::is_convertible_v<decltype(id), std::function<L()>>,
                  "id() must work as L()");
#else

template <typename V,
          V (*op)(V, V),
          V (*e)(),
          typename L,
          V (*mapping)(L, V),
          L (*composition)(L, L),
          L (*id)()>
class LazySegmentTree {

#endif
    int n;
    std::vector<V> value;
    std::vector<L> lazy;

    void push(const int i) {
        value[2 * i + 1] = mapping(lazy[i], value[2 * i + 1]);
        value[2 * i + 2] = mapping(lazy[i], value[2 * i + 2]);
        lazy[2 * i + 1] = composition(lazy[i], lazy[2 * i + 1]);
        lazy[2 * i + 2] = composition(lazy[i], lazy[2 * i + 2]);
        lazy[i] = id();
    }

    void set(int i, int l, int r, const int sl, const int sr, const L& x) {
        if (sl <= l && r <= sr) {
            value[i] = mapping(x, value[i]);
            lazy[i] = composition(x, lazy[i]);
            return;
        }
        push(i);
        if (sl < (l + r) / 2) {
            set(2 * i + 1, l, (l + r) / 2, sl, sr, x);
        }
        if (sr > (l + r) / 2) {
            set(2 * i + 2, (l + r) / 2, r, sl, sr, x);
        }
        value[i] = op(value[2 * i + 1], value[2 * i + 2]);
    }

    V get(int i, int l, int r, const int ql, const int qr) {
        if (ql <= l && r <= qr) {
            return value[i];
        }
        push(i);
        if (qr <= (l + r) / 2) {
            return get(2 * i + 1, l, (l + r) / 2, ql, qr);
        }
        if (ql >= (l + r) / 2) {
            return get(2 * i + 2, (l + r) / 2, r, ql, qr);
        }
        return op(get(2 * i + 1, l, (l + r) / 2, ql, qr), get(2 * i + 2, (l + r) / 2, r, ql, qr));
    }

   public:
    void set(const int l, const int r, const L& x) {
        return set(0, 0, n, l, r, x);
    }
    V get(const int l, const int r) {
        return get(0, 0, n, l, r);
    }
    LazySegmentTree(const int n) : n(n) {
        value.resize(n * 4);
        lazy.resize(n * 4);
        auto build = [&](auto& self, int i, int l, int r) -> void {
            if (l + 1 == r) {
                value[i] = e();
                lazy[i] = id();
                return;
            }
            self(self, 2 * i + 1, l, (l + r) / 2);
            self(self, 2 * i + 2, (l + r) / 2, r);
            value[i] = op(value[2 * i + 1], value[2 * i + 2]);
            lazy[i] = id();
        };
        build(build, 0, 0, n);
    }
    LazySegmentTree(const std::vector<V>& arr) {
        n = arr.size();
        value.resize(n * 4);
        lazy.resize(n * 4);
        auto build = [&](auto& self, int i, int l, int r) -> void {
            if (l + 1 == r) {
                value[i] = arr[l];
                lazy[i] = id();
                return;
            }
            self(self, 2 * i + 1, l, (l + r) / 2);
            self(self, 2 * i + 2, (l + r) / 2, r);
            value[i] = op(value[2 * i + 1], value[2 * i + 2]);
            lazy[i] = id();
        };
        build(build, 0, 0, n);
    }
};

#endif

using i64 = long long;

struct V {
    i64 sum;
    int size;
    int min;
};

V e() {
    return V{0LL, 1, 0};
}

V op(const V& l, const V& r) {
    return V{l.sum + r.sum, l.size + r.size, std::min(l.min, r.min)};
}

struct L {
    int cover;
};

V mapping(const L& x, const V& v) {
    if (x.cover == -1) {
        return v;
    } else {
        return V{1LL * x.cover * v.size, v.size, x.cover};
    }
}

L composition(const L& x, const L& y) {
    return (x.cover == -1) ? y : x;
}

L id() {
    return L{-1};
}

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<V> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].sum;
        a[i].size = 1;
        a[i].min = a[i].sum;
    }

    LazySegmentTree<V, op, e, L, mapping, composition, id> T(a);
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 3) {
            std::cout << T.get(0, n).sum << "\n";
        } else {
            int x;
            std::cin >> x;
            if (op == 1) {
                int m = T.get(0, x).min;
                T.set(0, x, L{m});
            } else {
                --x;
                int m = T.get(x, n).min;
                T.set(x, n, L{m});
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
