#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

const int P = 998244353;

constexpr int power(int base, int exp) {
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

constexpr int inv(int base) {
    return power(base, P - 2);
}

template <typename Value, typename Lazy>
struct LazySegmentTree {
    int n;
    std::vector<Value> value;
    std::vector<Lazy> lazy;

    void pull(const int id) {
        value[id] = value[2 * id + 1] + value[2 * id + 2];
    }

    void push(const int id) {
        value[2 * id + 1] += lazy[id];
        value[2 * id + 2] += lazy[id];
        lazy[2 * id + 1] += lazy[id];
        lazy[2 * id + 2] += lazy[id];
        lazy[id] = Lazy();
    }

    void set(int id, int l, int r, int sl, int sr, const Lazy& t) {
        if (sr <= l || sl >= r) {
            return;
        }
        if (sl <= l && r <= sr) {
            value[id] += t;
            lazy[id] += t;
            return;
        }
        push(id);
        set(2 * id + 1, l, (l + r) / 2, sl, sr, t);
        set(2 * id + 2, (l + r) / 2, r, sl, sr, t);
        pull(id);
    }

    Value get(int id, int l, int r, int gl, int gr) {
        if (gl <= l && r <= gr) {
            return value[id];
        }
        push(id);
        if (gr <= (l + r) / 2) {
            return get(2 * id + 1, l, (l + r) / 2, gl, gr);
        }
        if (gl >= (l + r) / 2) {
            return get(2 * id + 2, (l + r) / 2, r, gl, gr);
        }
        return get(2 * id + 1, l, (l + r) / 2, gl, gr) + get(2 * id + 2, (l + r) / 2, r, gl, gr);
    }

    LazySegmentTree(const int n) : n(n), value(4 * n), lazy(4 * n) {
        auto build = [&](auto& self, int id, int l, int r) {
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

    LazySegmentTree(const std::vector<Value>& info) : n(info.size()), value(4 * n), lazy(4 * n) {
        auto build = [&](auto& self, int id, int l, int r) {
            if (l + 1 == r) {
                value[id] = info[l];
                return;
            }
            lazy[id] = Lazy();
            self(self, 2 * id + 1, l, (l + r) / 2);
            self(self, 2 * id + 2, (l + r) / 2, r);
            pull(id);
        };
        build(build, 0, 0, n);
    }
};

struct Lazy {
    int chg;
    Lazy(const int chg) : chg(chg) {}
    Lazy() : chg(-1) {}
    Lazy& operator+=(const Lazy& x) {
        if (x.chg != -1) {
            chg = x.chg;
        }
        return *this;
    }
};

struct Value {
    int cnt, sz;
    Value(const int cnt, const int sz) : cnt(cnt), sz(sz) {}
    Value() : cnt(0), sz(0) {}
    Value& operator+=(const Lazy& x) {
        if (x.chg == 0) {
            cnt = 0;
        } else if (x.chg == 1) {
            cnt = sz;
        }
        return *this;
    }
};

Value operator+(const Value& x, const Value& y) {
    return Value(x.cnt + y.cnt, x.sz + y.sz);
}

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> l(m), r(m), k(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> l[i] >> r[i] >> k[i];
        --l[i], --k[i];
    }

    int ans = 0;
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    do {
        bool ok = true;
        for (int i = 0; i < m; ++i) {
            if (*std::max_element(perm.begin() + l[i], perm.begin() + r[i]) != k[i]) {
                ok = false;
                break;
            }
        }
        ans += ok;
    } while (std::next_permutation(perm.begin(), perm.end()));

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
