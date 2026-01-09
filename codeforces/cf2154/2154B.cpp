#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int max = 0;
    for (int i = 0; i < n; ++i) {
        max = std::max(max, a[i]);
        if (i & 1) {
            a[i] = max;
        }
    }

    i64 ans = 0;
    ans += std::max(a[0] - a[1] + 1, 0);
    if (n & 1) {
        ans += std::max(a[n - 1] - a[n - 2] + 1, 0);
    }
    for (int i = 2; i < n - 1; ++i) {
        if ((i & 1) == 0) {
            ans += std::max(a[i] - std::min(a[i - 1], a[i + 1]) + 1, 0);
        }
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