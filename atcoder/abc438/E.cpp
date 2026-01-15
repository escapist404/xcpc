#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using i64 = long long;

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        --a[i];
    }

    std::vector<std::vector<i64>> f(30, std::vector<i64>(n)), g(30, std::vector<i64>(n));
    for (int i = 0; i < n; ++i) {
        f[0][i] = a[i];
        g[0][i] = i + 1;
    }

    for (int i = 1; i < 30; ++i) {
        for (int j = 0; j < n; ++j) {
            f[i][j] = f[i - 1][f[i - 1][j]];
            g[i][j] = g[i - 1][j] + g[i - 1][f[i - 1][j]];
        }
    }

    for (int i = 0; i < q; ++i) {
        int t, b;
        std::cin >> t >> b;
        --b;
        
        i64 ans = 0;
        for (int j = 0; j < 30; ++j) {
            if (t >> j & 1) {
                ans += g[j][b];
                b = f[j][b];
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
