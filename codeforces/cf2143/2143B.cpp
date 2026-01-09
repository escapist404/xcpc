#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> b(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> b[i];
    }

    std::sort(a.begin(), a.end(), std::greater<int>());
    std::sort(b.begin(), b.end());

    int cur = 0;
    i64 ans = 0;
    for (int i = 0; i < k; ++i) {
        if (cur + b[i] <= n) {
            ans += std::accumulate(a.begin() + cur, a.begin() + cur + b[i] - 1, 0LL);
            cur += b[i];
        }
    }

    std::cout << ans + std::accumulate(a.begin() + cur, a.begin() + n, 0LL) << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}