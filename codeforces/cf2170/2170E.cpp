#include <bits/stdc++.h>

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
            lazy[i] = composition(lazy[i], x);
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
    void set(int l, int r, const L& x) {
        set(0, 0, n, l, r, x);
    }
    V get(int l, int r) {
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
        };
        build(build, 0, 0, n);
    }
    LazySegmentTree(const std::vector<V>& arr) {
        n = arr.size();
        value.resize(n * 4);
        auto build = [&](auto& self, int i, int l, int r) -> void {
            if (l + 1 == r) {
                value[i] = arr[l];
                lazy[i] = id();
                return;
            }
            self(self, 2 * i + 1, l, (l + r) / 2);
            self(self, 2 * i + 2, (l + r) / 2, r);
            value[i] = op(value[2 * i + 1], value[2 * i + 2]);
        };
        build(build, 0, 0, n);
    }
};

using i64 = long long;
const int P = 998244353;

int op(int x, int y) {
    return (x + y) % P;
}

int e() {
    return 0;
}

int id() {
    return -1;
}

int mapping(int x, int y) {
    if (x != id()) {
        return x;
    }
    return y;
}

int composition(int x, int y) {
    if (x != id()) {
        return x;
    }
    return y;
}

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> seg(n, 0);
    for (int i = 0; i < m; ++i) {
        int l, r;
        std::cin >> l >> r;
        --r;
        seg[r] = std::max(seg[r], l);
    }

    int one = 1;
    LazySegmentTree<int, op, e, int, mapping, composition, id> T(n);
    for (int i = 0; i < n; ++i) {
        if (seg[i] > 0) {
            T.set(0, seg[i], 0);
        }
        T.set(i, i + 1, one);
        one = T.get(0, n);
    }

    std::cout << 2 * T.get(0, n) % P << "\n";
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
