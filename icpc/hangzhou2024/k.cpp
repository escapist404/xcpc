#include <bits/stdc++.h>

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> p(n * m);
    std::vector<std::vector<int>> o(n);
    for (int i = 0; i < n * m; ++i) {
        std::cin >> p[i];
        --p[i];
        o[p[i] / m].push_back(i);
    }

    if (k >= m) {
        std::cout << m << "\n";
        return;
    }
    
    int ans = n * m;
    for (int i = 0; i < n; ++i) {
        int cur = o[i][m - k - 1];
        int empty = cur - m + k + 1;
        ans = std::min(ans, cur + std::max(k - empty, 0) + 1);
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