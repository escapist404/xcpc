#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> a[i][j];
        }
    }

    if (n == 1 && m == 1) {
        std::cout << -a[0][0] << "\n";
        return;
    }

    if (n == 1) {
        i64 s = 0, max = -1E9;
        for (int i = 0; i < m; ++i) {
            s += a[0][i];
            max = std::max(max, (i64)a[0][i]);
        }
        std::cout << s - 2 * max << "\n";
        return;
    }

    if (m == 1) {
        i64 s = 0, max = -1E9;
        for (int i = 0; i < n; ++i) {
            s += a[i][0];
            max = std::max(max, (i64)a[i][0]);
        }
        std::cout << s - 2 * max << "\n";
        return;
    }

    std::vector<std::vector<i64>> f(n, std::vector<i64>(m));
    f[0][0] = a[0][0];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            i64 tr = -1E18;
            if (i) {
                tr = std::max(tr, f[i - 1][j] + a[i][j]);
            }
            if (j) {
                tr = std::max(tr, f[i][j - 1] + a[i][j]);
            }
            f[i][j] = tr;
        }
    }

    std::vector<std::vector<i64>> g(n, std::vector<i64>(m));
    g[n - 1][m - 1] = a[n - 1][m - 1];
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (i == n - 1 && j == m - 1) {
                continue;
            }
            i64 tr = -1E18;
            if (i < n - 1) {
                tr = std::max(tr, g[i + 1][j] + a[i][j]);
            }
            if (j < m - 1) {
                tr = std::max(tr, g[i][j + 1] + a[i][j]);
            }
            g[i][j] = tr;
        }
    }

    std::vector<std::vector<i64>> pmax(n, std::vector<i64>(m));
    for (int i = 0; i < n - 1; ++i) {
        pmax[i][0] = f[i][0] + g[i + 1][0];
        for (int j = 1; j < m; ++j) {
            pmax[i][j] = std::max(pmax[i][j - 1], f[i][j] + g[i + 1][j]);
        }
    }

    std::vector<std::vector<i64>> smax(n, std::vector<i64>(m));
    for (int i = 1; i < n; ++i) {
        smax[i][m - 1] = f[i - 1][m - 1] + g[i][m - 1];
        for (int j = m - 2; j >= 0; --j) {
            smax[i][j] = std::max(smax[i][j + 1], f[i - 1][j] + g[i][j]);
        }
    }

    i64 ans = 1E18;
    ans = std::min({ans, g[0][0] - 2LL * a[0][0], f[n - 1][m - 1] - 2LL * a[n - 1][m - 1]});
    for (int i = 1; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            i64 inclusive = f[i][j] + g[i][j] - 3LL * a[i][j];
            i64 exclusive = -1E18;
            if (j > 0) {
                exclusive = std::max(exclusive, pmax[i][j - 1]);
            }
            if (j < m - 1) {
                exclusive = std::max(exclusive, smax[i][j + 1]);
            }
            ans = std::min(ans, std::max(inclusive, exclusive));
        }
    }
    for (int j = 1; j < m; ++j) {
        i64 inclusive = f[0][j] + g[0][j] - 3LL * a[0][j];
        i64 exclusive = pmax[0][j - 1];
        ans = std::min(ans, std::max(inclusive, exclusive));
    }
    for (int j = 0; j < m - 1; ++j) {
        i64 inclusive = f[n - 1][j] + g[n - 1][j] - 3LL * a[n - 1][j];
        i64 exclusive = smax[n - 1][j + 1];
        ans = std::min(ans, std::max(inclusive, exclusive));
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
