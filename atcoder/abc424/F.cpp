#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

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

const int P = 998'244'353;

int power(int base, int exp) {
    int ret = 1;
    while (exp) {
        if (exp & 1) {
            ret = 1LL * ret * base % P;
        }
        base = 1LL * base * base % P;
        exp >>= 1;
    }
    return ret;
}

struct V {
    int w;
    V() : w(1) {}
    V(const int w) : w(w) {}
};

V operator+(const V& l, const V& r) {
    return 1LL * l.w * r.w % P;
}

int main() {
    std::mt19937 rnd(time(0));

    int n, q;
    std::cin >> n >> q;

    SegmentTree<V> T(n);

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        --l;
        if (T.get(l, r).w == 1) {
            std::cout << "Yes\n";
            int v = rnd() % P;
            T.set(l, V(v));
            T.set(r - 1, V(power(v, P - 2)));
        } else {
            std::cout << "No\n";
        }
    }

    return 0;
}
