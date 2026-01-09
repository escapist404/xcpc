#include <bits/stdc++.h>

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> c(n + 1);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        c[x]++;
    }

    int ans = 0;
    for (int i = 0; i < k; ++i) {
        if (c[i] == 0) {
            ans++;
        }
    }
    ans = std::max(ans, c[k]);

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}