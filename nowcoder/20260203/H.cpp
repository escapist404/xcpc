#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

const int P = 998244353;

template <typename Value>
class Segtree {
    int n;
    std::vector<Value> value;

    void pull(const int idx) {
        value[idx] = value[2 * idx + 1] + value[2 * idx + 2];
    }
    
public:
    void set(const int i, const int l, const int r, const int x, const Value& v) {
        if (l + 1 == r) {
            value[i] = v;
            return;
        }
        if ((l + r) / 2 <= x) {
            set(2 * i + 2, (l + r) / 2, r, x, v);
        } else {
            set(2 * i + 1, l, (l + r) / 2, x, v);
        }
        pull(i);
    }

    Value get(const int i, const int l, const int r, const int gl, const int gr) const {
        if (gl >= gr) {
            return Value();
        }
        if (gl <= l && r <= gr) {
            return value[i];
        }
        if (gr <= (l + r) / 2) {
            return get(2 * i + 1, l, (l + r) / 2, gl, gr);
        } else if (gl >= (l + r) / 2) {
            return get(2 * i + 2, (l + r) / 2, r, gl, gr);
        } else {
            return get(2 * i + 1, l, (l + r) / 2, gl, gr) + get(2 * i + 2, (l + r) / 2, r, gl, gr);
        }
    }

    Segtree(const int n) : n(n), value(4 * n) {
        auto build = [&](auto& self, int i, int l, int r) {
            if (l + 1 == r) {
                value[i] = Value();
                return;
            }
            self(self, 2 * i + 1, l, (l + r) / 2);
            self(self, 2 * i + 2, (l + r) / 2, r);
            pull(i);
        };
        build(build, 0, 0, n);
    }
};

struct Value {
    int x;
    Value(const int x) : x(x) {}
    Value() : x(0) {}
};

Value operator+(const Value& l, const Value& r) {
    return Value((l.x + r.x) % P);
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    Segtree<Value> T(n);

    std::vector<int> p(31, -1), q(31, -1);
    std::vector<int> l(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 31; ++j) {
            if (a[i] >> j & 1) {
                p[j] = q[j];
                q[j] = i;
            }
        }
        l[i] = *std::max_element(p.begin(), p.end());
    }

    for (int i = 0; i < n; ++i) {
        T.set(0, 0, n, i, Value((T.get(0, 0, n, l[i], i).x + (l[i] == -1)) % P));
    }

    std::cout << T.get(0, 0, n, n - 1, n).x << "\n";
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
