#include <bits/stdc++.h>

#ifndef SEGTREE_HPP
#define SEGTREE_HPP

#include <vector>
#include <type_traits>

#if __cplusplus >= 201703L

template <typename V, auto op, auto e>
class SegmentTree {
    static_assert(std::is_convertible_v<decltype(op), std::function<V(V, V)>>,
                  "op() must work as V(V, V)");
    static_assert(std::is_convertible_v<decltype(e), std::function<V()>>,
                  "e() must work as V()");

#else

template <typename V, V (*op)(V, V), V (*e)()>
class SegmentTree {

#endif

    int n;
    std::vector<V> value;

    void set(int id, int l, int r, const int spos, const V& sval) {
        if (l + 1 == r) {
            value[id] = sval;
            return;
        }
        if (spos < (l + r) / 2) {
            set(2 * id + 1, l, (l + r) / 2, spos, sval);
        }
        if (spos >= (l + r) / 2) {
            set(2 * id + 2, (l + r) / 2, r, spos, sval);
        }
        value[id] = op(value[2 * id + 1], value[2 * id + 2]);
    }

    V get(int id, int l, int r, const int ql, const int qr) const {
        if (ql <= l && r <= qr) {
            return value[id];
        }
        if (ql >= (l + r) / 2) {
            return get(2 * id + 2, (l + r) / 2, r, ql, qr);
        }
        if (qr <= (l + r) / 2) {
            return get(2 * id + 1, l, (l + r) / 2, ql, qr);
        }
        return op(get(2 * id + 1, l, (l + r) / 2, ql, qr), get(2 * id + 2, (l + r) / 2, r, ql, qr));
    }

   public:
    SegmentTree(const int n) : n(n) {
        value.resize(n * 4);
        auto build = [&](auto& self, int id, int l, int r) -> void {
            if (l + 1 == r) {
                value[id] = e();
                return;
            }
            self(self, 2 * id + 1, l, (l + r) / 2);
            self(self, 2 * id + 2, (l + r) / 2, r);
            value[id] = op(value[2 * id + 1], value[2 * id + 2]);
        };
        build(build, 0, 0, n);
    }
    SegmentTree(const std::vector<V>& arr) {
        n = arr.size();
        value.resize(n * 4);
        auto build = [&](auto& self, int id, int l, int r) -> void {
            if (l + 1 == r) {
                value[id] = arr[l];
                return;
            }
            self(self, 2 * id + 1, l, (l + r) / 2);
            self(self, 2 * id + 2, (l + r) / 2, r);
            value[id] = op(value[2 * id + 1], value[2 * id + 2]);
        };
        build(build, 0, 0, n);
    }

    void set(const int p, const V& v) {
        set(0, 0, n, p, v);
    }
    V get(const int p) const {
        return get(0, 0, n, p, p + 1);
    }
    V get(const int l, const int r) const {
        return get(0, 0, n, l, r);
    }
    V get() const {
        return value.front();
    }
};

#endif

using i64 = long long;

struct Value {
    int lsize, rsize, msize, all;
    char ltype, rtype;
};

Value op(const Value& x, const Value& y) {
    Value z {};
    z.lsize = x.lsize + ((x.lsize == x.all && y.ltype == x.ltype) ? y.lsize : 0);
    z.rsize = y.rsize + ((y.rsize == y.all && y.rtype == x.rtype) ? x.rsize : 0);
    z.all = x.all + y.all;    
    z.ltype = x.ltype;
    z.rtype = y.rtype;
    z.msize = std::max({x.msize, y.msize, (x.rtype == y.ltype) ? (x.rsize + y.lsize) : 0});
    return z;
}

Value e() {
    return Value {1, 1, 1, 1, '*', '*'};
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int N, Q;
    std::string S;
    std::cin >> N >> Q >> S;

    std::vector<Value> info(N, e());
    for (int i = 0; i < N; ++i) {
        info[i].ltype = info[i].rtype = S[i];
    }

    SegmentTree<Value, op, e> T(info);

    for (int i = 0; i < Q; ++i) {
        int type;
        std::cin >> type;
        if (type == 2) {
            int l, r;
            std::cin >> l >> r;
            --l;
            std::cout << T.get(l, r).msize << "\n";
        } else {
            int x;
            char c;
            std::cin >> x >> c;
            --x;
            T.set(x, Value {1, 1, 1, 1, c, c});
        }
    }

    return 0;
}
