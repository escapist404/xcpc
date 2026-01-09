#include <bits/stdc++.h>

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

using i64 = long long;

int main() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> info(n);
    for (int i = 0; i < n; ++i) {
        auto& [v, p] = info[i];
        std::cin >> v;
        p = i;
    }

    SegmentTree<std::pair<int, int>, [](auto x, auto y) { return std::max(x, y); }, []() { return std::make_pair(0, 0); }> T(info);

    auto recursion = [&](auto& self, int l, int r) -> i64 {
        int m = T.get(l, r).second;
        i64 x = 0;
        if (m > l) {
            int f = T.get(l, m).second;
            x = std::max(x, self(self, l, m) + m - f);
        }
        if (m + 1 < r) {
            int f = T.get(m + 1, r).second;
            x = std::max(x, self(self, m + 1, r) + f - m);
        }
        return x;
    };

    std::cout << recursion(recursion, 0, n) << "\n";
    return 0;
}
