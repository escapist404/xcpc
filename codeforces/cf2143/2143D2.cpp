#include <bits/stdc++.h>

using i64 = long long;

const int P = 1'000'000'007;

template <typename T>
class FenwickTree {
    int n;
    std::vector<T> data;
public:
    void add(int x, T d) {
        for (int i = x + 1; i <= n; i += i & (-i)) {
            data[i] += d;
        }
    }
    T sum(int x) {
        T s = 0;
        for (int i = x; i > 0; i -= i & (-i)) {
            s = data[i] + s;
        }
        return s;
    }   
    FenwickTree(const int n) : n(n), data(n + 1) {}
};

struct Z {
    int v;
    Z& operator+= (const Z& x) {
        v += x.v;
        if (v >= P) {
            v -= P;
        }
        return *this;
    }
    Z& operator-= (const Z& x) {
        v -= x.v;
        if (v < 0) {
            v += P;
        }
        return *this;
    }
    friend Z operator+ (const Z& x, const Z& y) {
        auto z = x;
        z += y;
        return z;
    }
    friend Z operator- (const Z& x, const Z& y) {
        auto z = x;
        z -= y;
        return z;
    }
    Z(const int v = 0) : v((v % P + P) % P) {}
};

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<FenwickTree<Z>> r(n + 1, FenwickTree<Z>(n + 1)), c(n + 1, FenwickTree<Z>(n + 1));
    r[0].add(0, 1);
    c[0].add(0, 1);

    for (int i = 0; i < n; ++i) {
        std::vector<std::tuple<int, int, Z>> chg;

        for (int j = a[i] + 1; j <= n; ++j) {
            auto d = r[j].sum(a[i] + 1);
            chg.emplace_back(j, a[i], d);
        }
        for (int k = 0; k < a[i]; ++k) {
            auto d = c[k].sum(a[i] + 1);
            chg.emplace_back(a[i], k, d);
        }

        for (const auto& [j, k, d] : chg) {
            r[j].add(k, d);
            c[k].add(j, d);
        }
    }

    Z ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans += r[i].sum(std::max(i, 1));
    }

    std::cout << ans.v << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}