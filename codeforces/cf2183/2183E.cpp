#include <bits/stdc++.h>

using i64 = long long;
const int P = 998244353;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    if (a[0] != 0 && a[0] != 1) {
        std::cout << 0 << "\n";
        return;
    }

    int ans = 0;
    std::vector<std::vector<int>> f(n, std::vector<int>(m + 1));
    f[0][1] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (f[i - 1][j] == 0) {
                continue;
            }
            for (int x = 1; x * x <= j; ++x) {
                if (j % x == 0) {
                    if (j + x <= m) {
                        (f[i][j + x] += f[i - 1][j]) %= P;
                    }
                    if (j / x != x && j + j / x <= m) {
                        (f[i][j + j / x] += f[i - 1][j]) %= P;
                    }
                }
            }
        }
        if (a[i] != 0) {
            int v = f[i][a[i]];
            f[i] = std::vector<int>(m + 1, 0);
            f[i][a[i]] = v;
        }
    }

    std::cout << std::accumulate(f[n - 1].begin(), f[n - 1].end(), 0LL, [](auto x, auto y) {
        return (x + y) % P;
    }) << "\n";
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