#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using i64 = long long;

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

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
        --b[i];
    }

    std::vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        r[b[i]] = i;
    }

    SegmentTree<int> T(n);

    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        T.set(r[i], 1);
        ans += 1LL * T.get(0, r[i] + 1) * T.get(r[i], n);    
    }

    std::cout << ans << "\n";
    return 0;
}
