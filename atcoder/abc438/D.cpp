#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

template <typename V, typename L>
class LazySegmentTree {
    int n;
    std::vector<V> value;
    std::vector<L> lazy;

    void push(const int ix) {
        value[2 * ix + 1] += lazy[ix];
        value[2 * ix + 2] += lazy[ix];
        lazy[2 * ix + 1] += lazy[ix];
        lazy[2 * ix + 2] += lazy[ix];
        lazy[ix] = L();
    }

    void pull(const int ix) {
        value[ix] = value[2 * ix + 1] + value[2 * ix + 2];
    }

    void set(const int ix, const int il, const int ir, const int l, const int r, const L& t) {
        if (l <= il && ir <= r) {
            value[ix] += t;
            lazy[ix] += t;
            return;
        }
        push(ix);
        int im = (il + ir) / 2;
        if (r > im) {
            set(2 * ix + 2, im, ir, l, r, t);
        }
        if (l < im) {
            set(2 * ix + 1, il, im, l, r, t);
        }
        pull(ix);
    }

    V get(const int ix, const int il, const int ir, const int l, const int r) {
        if (l <= il && ir <= r) {
            return value[ix];
        }
        push(ix);
        int im = (il + ir) / 2;
        if (r <= im) {
            return get(2 * ix + 1, il, im, l, r);
        }
        if (l >= im) {
            return get(2 * ix + 2, im, ir, l, r);
        }
        return get(2 * ix + 1, il, im, l, r) + get(2 * ix + 2, im, ir, l, r);
    }

  public:
    LazySegmentTree(const int n) : n(n), value(4 * n), lazy(4 * n) {
        auto build = [&](auto& self, const int ix, const int il, const int ir) -> void {
            if (il + 1 == ir) {
                value[ix] = V();
                lazy[ix] = L();
                return;
            }
            int im = (il + ir) / 2;
            self(self, 2 * ix + 1, il, im);
            self(self, 2 * ix + 2, im, ir);
            pull(ix);
        };
        build(build, 0, 0, n);
    }
    LazySegmentTree(const std::vector<V>& info) : n(info.size()), value(4 * n), lazy(4 * n) {
        auto build = [&](auto& self, const int ix, const int il, const int ir) -> void {
            if (il + 1 == ir) {
                value[ix] = info[il];
                lazy[ix] = L();
                return;
            }
            int im = (il + ir) / 2;
            self(self, 2 * ix + 1, il, im);
            self(self, 2 * ix + 2, im, ir);
            pull(ix);
        };
        build(build, 0, 0, n);
    }
    void set(const int l, const int r, const L& t) {
        set(0, 0, n, l, r, t);
    }
    V get(const int l, const int r) {
        return get(0, 0, n, l, r);
    }
};

using i64 = long long;

struct V {
    i64 max;
    V() : max(0) {}
    V(const i64 max) : max(max) {}
};

struct L {
    i64 add;
    L() : add(0) {}
    L(const i64 add) : add(add) {}
};

V operator+(const V& lhs, const V& rhs) {
    return V(std::max(lhs.max, rhs.max));
}

V& operator+=(V& lhs, const L& rhs) {
    lhs.max += rhs.add;
    return lhs;
}

L& operator+=(L& lhs, const L& rhs) {
    lhs.add += rhs.add;
    return lhs;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n), c(n);
    for (auto& i : a) {
        std::cin >> i;
    }
    for (auto& i : b) {
        std::cin >> i;
    }
    for (auto& i : c) {
        std::cin >> i;
    }

    LazySegmentTree<V, L> T(n);
    i64 ans = 0;
    i64 sufc = std::accumulate(c.begin() + 2, c.end(), 0LL);
    i64 prea = a[0] + a[1];
    T.set(1, 2, L(a[0] + b[1]));

    for (int i = 2; i < n; ++i) {
        ans = std::max(T.get(0, n).max + sufc, ans);
        T.set(i, i + 1, prea);
        T.set(1, i + 1, b[i]);
        prea += a[i];
        sufc -= c[i];
    }

    std::cout << ans << "\n";

    return 0;
}
