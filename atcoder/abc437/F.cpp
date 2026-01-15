#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

template <typename Value>
class SegmentTree {
    int n;
    std::vector<Value> value;

    void pull(const int id) {
        value[id] = value[2 * id + 1] + value[2 * id + 2];
    }

    void set(const int id, const int l, const int r, const int p, const Value& v) {
        if (l + 1 == r) {
            value[id] = v;
            return;
        }
        if ((l + r) / 2 <= p) {
            set(2 * id + 2, (l + r) / 2, r, p, v);
        } else {
            set(2 * id + 1, l, (l + r) / 2, p, v);
        }
        pull(id);
    }

    Value get(const int id, const int l, const int r, const int L, const int R) const {
        if (L <= l && r <= R) {
            return value[id];
        }
        if ((l + r) / 2 >= R) {
            return get(2 * id + 1, l, (l + r) / 2, L, R);
        } else if ((l + r) / 2 <= L) {
            return get(2 * id + 2, (l + r) / 2, r, L, R);
        } else {
            return get(2 * id + 1, l, (l + r) / 2, L, R) + get(2 * id + 2, (l + r) / 2, r, L, R);
        }
    }

public:
    void set(const int p, const Value& v) {
        set(0, 0, n, p, v);
    }
    Value get(const int l, const int r) const {
        return get(0, 0, n, l, r);
    }
    SegmentTree(const int n) : n(n), value(4 * n) {
        auto build = [&](auto& self, int id, int l, int r) -> void {
            if (l + 1 == r) {
                value[id] = Value();
                return;
            }
            self(self, 2 * id + 1, l, (l + r) / 2);
            self(self, 2 * id + 2, (l + r) / 2, r);
            pull(id);
        };
        build(build, 0, 0, n);
    }
    SegmentTree(const std::vector<Value>& v_array) : n(v_array.size()), value(4 * v_array.size()) {
        auto build = [&](auto& self, int id, int l, int r) -> void {
            if (l + 1 == r) {
                value[id] = v_array[l];
                return;
            }
            self(self, 2 * id + 1, l, (l + r) / 2);
            self(self, 2 * id + 2, (l + r) / 2, r);
            pull(id);
        };
        build(build, 0, 0, n);
    }
};

struct V {
    int min, max;
    V() : min(2E9), max(-2E9) {}
    V(const int min, const int max) : min(min), max(max) {}
};

V operator+(const V& l, const V& r) {
    return V(std::min(l.min, r.min), std::max(l.max, r.max));
}

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<V> f(n), g(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        f[i] = V(x + y, x + y);
        g[i] = V(y - x, y - x);
    }

    SegmentTree<V> F(f), G(g);
    while (q--) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int i, x, y;
            std::cin >> i >> x >> y;
            --i;
            f[i] = V(x + y, x + y);
            g[i] = V(y - x, y - x);
            F.set(i, f[i]);
            G.set(i, g[i]);
        } else {
            int l, r, x, y;
            std::cin >> l >> r >> x >> y;
            --l;
            int cf = x + y;
            int cg = y - x;
            auto [minf, maxf] = F.get(l, r);
            auto [ming, maxg] = G.get(l, r);
            std::cout << std::max({llabs(1LL * minf - cf), llabs(1LL * maxf - cf), llabs(1LL * ming - cg), llabs(1LL * maxg - cg)}) << "\n";
        }
    }

    return 0;
}
