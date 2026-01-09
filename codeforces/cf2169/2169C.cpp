#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<i64> p(n + 1);
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] + a[i];
    }

    i64 ans = std::accumulate(a.begin(), a.end(), 0LL);
    i64 before = 0;
    for (int i = 1; i <= n; ++i) {
        before = std::max(p[i - 1] - 1LL * i * i + i, before);
        ans = std::max(before + 1LL * i * i + i + p[n] - p[i], ans);
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }
    
    return 0;
}
