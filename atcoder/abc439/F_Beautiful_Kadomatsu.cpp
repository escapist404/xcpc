#include <bits/stdc++.h>

struct Fenwick {
    int n;
    std::vector<int> d;

    int ask(int x) const {
        int s = 0;
        while (x) {
            s += d[x];
            x -= x & (-x);
        }
        return s;
    }

    int sum(int l, int r) const {
        return ask(r) - ask(l);
    }

    void add(int x, int c) {
        ++x;
        while (x <= n) {
            d[x] += c;
            x += x & (-x);
        }
    }

    Fenwick(const int n) : n(n), d(n + 1) {}
};

using i64 = long long;
const int P = 998244353;

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        --a[i];
    }

    std::vector<int> f(n), g(n);
    
    Fenwick T(n);
    for (int i = 0; i < n; ++i) {
        f[i] = T.sum(0, a[i]);
        T.add(a[i], 1);
    }

    T = Fenwick(n);
    for (int i = n - 1; i >= 0; --i) {
        g[i] = T.sum(0, a[i]);
        T.add(a[i], 1);
    }

    int ans = 0, acc = 0;
    for (int i = 0; i < n; ++i) {
        (ans += 1LL * (acc + f[i]) * g[i] % P) %= P;
        (acc *= 2) %= P;
        (acc += f[i]) %= P;
    }

    std::cout << ans << "\n";

    return 0;
}
