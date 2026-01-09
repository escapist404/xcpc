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
        };
        build(build, 0, 0, n);
    }

    void set(const int l, const int r, const L& x) {
        set(0, 0, n, l, r, x);
    }

    V get(const int l, const int r) {
        return get(0, 0, n, l, r);
    }
};

#endif

std::pair<int, int> op(const std::pair<int, int>& x, const std::pair<int, int>& y) {
    return {x.first + y.first, x.second + y.second};
}

std::pair<int, int> e() {
    return {0, 1};
}

std::pair<int, int> mapping(const int x, const std::pair<int, int>& y) {
    if (x == 1) {
        return {y.second, y.second};
    } else {
        return {y.first, y.second};
    }
}

int composition(const int x, const int y) {
    if (x == 1) {
        return x;
    }
    return y;
}

int id() {
    return 0;
}

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> idx = {0, n};
    std::vector<std::pair<int, int>> qseg(q);

    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        --l;
        qseg[i] = {l, r};
        idx.push_back(l);
        idx.push_back(r);
    }

    std::sort(idx.begin(), idx.end());
    idx.erase(std::unique(idx.begin(), idx.end()), idx.end());

    std::vector<std::pair<int, int>> cseg(idx.size() - 1);
    for (int i = 0; i < (int)idx.size() - 1; ++i) {
        cseg[i].second = idx[i + 1] - idx[i];
    }

    LazySegmentTree<std::pair<int, int>, op, e, int, mapping, composition, id> T(cseg);

    for (int i = 0; i < q; ++i) {
        auto [l, r] = qseg[i];
        int cl = std::lower_bound(idx.begin(), idx.end(), l) - idx.begin();
        int cr = std::lower_bound(idx.begin(), idx.end(), r) - idx.begin();

        T.set(cl, cr, 1);
        std::cout << n - T.get(0, (int)cseg.size()).first << "\n";
    }

    return 0;
}
