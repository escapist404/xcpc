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

    void set(int l, int r, const L& x) {
        set(0, 0, n, l, r, x);
    }

    V get(int l, int r) {
        return get(0, 0, n, l, r);
    }
};

std::pair<i64, int> op(std::pair<i64, int> x, std::pair<i64, int> y) {
    return std::make_pair(x.first + y.first, x.second + y.second);
}

std::pair<i64, int> e() {
    return std::make_pair(0, 1);
}

std::pair<i64, int> mapping(int x, std::pair<i64, int> y) {
    return std::make_pair(y.first + 1LL * x * y.second, y.second);
}

int composition(int x, int y) {
    return x + y;
}

int id() {
    return 0;
}

const int M = 5E5;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, Q;
    std::cin >> N >> Q;

    LazySegmentTree<std::pair<i64, int>, op, e, int, mapping, composition, id> S(M + 1), T(M + 1);

    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
        S.set(A[i], A[i] + 1, A[i]);
        T.set(A[i], A[i] + 1, 1);
    }

    for (int i = 0; i < Q; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int x, y;
            std::cin >> x >> y;
            --x;
            S.set(A[x], A[x] + 1, -A[x]);
            T.set(A[x], A[x] + 1, -1);
            A[x] = y;
            S.set(A[x], A[x] + 1, A[x]);
            T.set(A[x], A[x] + 1, 1);
        } else {
            int l, r;
            std::cin >> l >> r;

            if (l >= r) {
                std::cout << 1LL * N * l << "\n";
            } else {
                auto [v1, s1] = T.get(0, l);
                auto [v2, s2] = S.get(l, r);
                auto [v3, s3] = T.get(r, M + 1);
                std::cout << v1 * l + v2 + v3 * r << "\n";
            }
        }
    }
    
    return 0;
}
