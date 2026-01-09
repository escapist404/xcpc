#include <bits/stdc++.h>

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> c(4 * n + 1);
    for (int i = 0, x; i < n; ++i) {
        std::cin >> x;
        c[x]++;
    }

    int pre = 0, ans = 0;
    for (int i = 4; i <= n; ++i) {
        pre += c[i];
    }
    for (int d = 1; d <= n; ++d) {
        if (n - pre - c[d] - c[2 * d] - c[3 * d] <= k) {
            ans = d;
        }
        for (int j = 4 * d; j <= 4 * d + 3; ++j) {
            pre -= c[j];
        }
    }

    std::cout << ans << "\n";
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
