#include <bits/stdc++.h>

using i64 = long long;

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
    void set(const int l, const int r, const L& x) {
        if (l < r) {
            set(0, 0, n, l, r, x);
        }
    }
    V get(const int l, const int r) {
        if (l < r) {
            return get(0, 0, n, l, r);
        } else {
            return e();
        }
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

i64 op(const i64 x, const i64 y) {
    return std::max(x, y);
}

i64 e() {
    return -(i64)1E18;
}

i64 mapping(const i64 x, const i64 y) {
    return x + y;
}

i64 composition(const i64 x, const i64 y) {
    return x + y;
}

i64 id() {
    return 0LL;
}

void solve() {
    int n;
    std::cin >> n;

    LazySegmentTree<i64, op, e, i64, mapping, composition, id> T(n);

    std::vector<i64> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    i64 sum = std::accumulate(a.begin(), a.end(), 0LL);
    i64 ans = -1E18;
    for (int i = 0; i < n; ++i) {
        sum -= a[i];
        i64 max = i > 0 ? T.get(0, i) : 0LL;
        ans = std::max(ans, max - sum);
        i64 ori = T.get(i, i + 1);
        T.set(i, i + 1, max + a[i] - ori);
        T.set(0, i, -a[i]);
    }

    std::cout << ans << "\n";
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
