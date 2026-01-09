#include <bits/stdc++.h>

void solve() {
    int n, m, p, x, a, b, c;
    std::cin >> n >> m >> p >> x >> a >> b >> c;

    std::unordered_map<int, int> occ;
    x = (1LL * a * x % p * x % p + 1LL * b * x % p + c) % p;
    int t = 0;
    while (occ.count(x) == false && t < n + m) {
        occ[x] = t;
        x = (1LL * a * x % p * x % p + 1LL * b * x % p + c) % p;
        t++;
    }

    if (occ.count(x) == false) {
        std::cout << 0 << "\n";
        return;
    }

    int s = occ[x];
    int r = t - s;

    if (s >= n) {
        std::cout << 0 << "\n";
        return;
    }

    n -= s;
    int ans1 = std::min(n, n + m - (n / r + (n % r > 0)) * r);
    int ans2 = std::min(m, n - n % r);

    std::cout << std::max({ans1, ans2, 0}) << "\n";
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}