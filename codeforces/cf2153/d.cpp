#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    using i64 = long long;

    auto find = [n](const std::vector<int>& a) {
        std::vector<i64> f(n + 1, 2e14);
        f[0] = 0;
        f[2] = abs(a[0] - a[1]);
        for (int i = 3; i <= n; ++i) {
            f[i] = std::min(f[i - 2] + abs(a[i - 1] - a[i - 2]), f[i - 3] + std::max({a[i - 1], a[i - 2], a[i - 3]}) - std::min({a[i - 1], a[i - 2], a[i - 3]}));
        }

        return f[n];
    };

    i64 ans = 2e14;
    for (int i = 0; i < 4 && i < n; ++i) {
        ans = std::min(ans, find(a));
        a.push_back(a.front());
        a.erase(a.begin());
    }

    std::cout << ans << "\n";
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
