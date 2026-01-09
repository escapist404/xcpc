#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> ra = {0}, p = {-1};
    for (int i = 0; i < n; ++i) {
        if (ra.back() < a[i]) {
            ra.push_back(a[i]);
            p.push_back(i);
        }
    }

    int m = ra.size();
    std::vector<std::vector<i64>> f(m, std::vector<i64>(k + 1));
    for (int i = 1; i < m; ++i) {
        for (int j = ra[i]; j <= k; ++j) {
            for (int u = 0; u < i; ++u) {
                f[i][j] = std::max(f[i][j], f[u][j - ra[i]] + 1LL * (p[i] - p[u] - 1) * ra[u] + ra[i]);
            }
        }
    }

    i64 ans = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = ra[i]; j <= k; ++j) {
            ans = std::max(ans, f[i][j] + 1LL * (n - p[i] - 1) * ra[i]);
            for (int l = i + 1; l < m; ++l) {
                i64 cur = std::max(ra[i], std::min(ra[l], k - j));
                ans = std::max(ans, f[i][j] + 1LL * (p[l] - p[i] - 1) * ra[i] + 1LL * (n - p[l]) * cur);
            }
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
