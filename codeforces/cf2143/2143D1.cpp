#include <bits/stdc++.h>

using i64 = long long;

const int P = 1'000'000'007;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<std::vector<int>> f(n + 1, std::vector<int>(n + 1));
    f[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        std::vector<std::vector<int>> g(f);
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k < j || k == 0; ++k) {
                if (j > a[i] && a[i] >= k) {
                    (g[j][a[i]] += f[j][k]) %= P;
                } else if (a[i] >= j) {
                    (g[a[i]][k] += f[j][k]) %= P;
                }
            }
        }
        std::swap(f, g);
    }

    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < i || j == 0; ++j) {
            (ans += f[i][j]) %= P;
        }
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}