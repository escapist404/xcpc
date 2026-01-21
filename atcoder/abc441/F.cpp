#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    
    int n, m;
    std::cin >> n >> m;
    std::vector<int> p(n), v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i] >> v[i];
    }

    std::vector<std::vector<i64>> f(n + 1, std::vector<i64>(m + 1));
    for (int i = 0; i < n; ++i) {
        f[i + 1] = f[i];
        for (int j = m; j >= p[i]; --j) {
            f[i + 1][j] = std::max(f[i][j], f[i][j - p[i]] + v[i]);
        }
    }

    std::vector<std::vector<i64>> g(n + 1, std::vector<i64>(m + 1));
    for (int i = n - 1; i >= 0; --i) {
        g[i] = g[i + 1];
        for (int j = m; j >= p[i]; --j) {
            g[i][j] = std::max(g[i + 1][j], g[i + 1][j - p[i]] + v[i]);
        }
    }

    i64 mv = f[n][m];
    for (int i = 0; i < n; ++i) {
        i64 iv = 0, ev = 0;
        for (int j = 0; j <= m; ++j) {
            iv = std::max(iv, f[i][j] + g[i + 1][m - j]);
        }
        for (int j = 0; j <= m - p[i]; ++j) {
            ev = std::max(ev, f[i][j] + g[i + 1][m - p[i] - j]);
        }
        if (ev == mv - v[i] && iv == mv) {
            std::cout << "B";
        } else if (ev == mv - v[i]) {
            std::cout << "A";
        } else {
            std::cout << "C";
        }
    }

    std::cout << "\n";

    return 0;
}
