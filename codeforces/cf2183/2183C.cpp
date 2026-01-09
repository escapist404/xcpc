#include <bits/stdc++.h>

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    --k;

    int ans = 1;
    for (int i = 0; i < k; ++i) {
        int first = 2 * (k - i) - 1;
        if (first <= m) {
            int r = m - first;
            int s = std::min({r, k - i, n - k - 1});
            ans = std::max(ans, s + 1 + k - i);
        }
    }
    for (int i = k + 1; i < n; ++i) {
        int first = 2 * (i - k) - 1;
        if (first <= m) {
            int r = m - first;
            int s = std::min({r, i - k, k});
            ans = std::max(ans, s + 1 + i - k);
        }
    }

    std::cout << ans << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}