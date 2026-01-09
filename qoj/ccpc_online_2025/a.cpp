#include <bits/stdc++.h>

int main() {
    int n, m;
    std::cin >> n >> m;

    using i64 = long long;
    std::vector<std::vector<i64>> d(n + 2, std::vector<i64>(m + 2));
    for (int a = 0; a <= n; ++a) {
        for (int b = 0; b <= m; ++b) {
            int l = std::min({a, b, n - a, m - b});
            d[a - l][b - l]++;
            d[a - l][b + l + 1]--;
            d[a + l + 1][b - l]--;
            d[a + l + 1][b + l + 1]++;
            d[a][b]--;
            d[a][b + 1]++;
            d[a + 1][b]++;
            d[a + 1][b + 1]--;
        }
    }

    for (int a = 0; a < n; ++a) {
        for (int b = 0; b < m; ++b) {
            int l = std::min({a, b, n - 1 - a, m - 1 - b});
            d[a - l][b - l]++;
            d[a + 2 + l][b - l]--;
            d[a - l][b + 2 + l]--;
            d[a + 2 + l][b + 2 + l]++;
        }
    }

    for (int a = 0; a <= n + 1; ++a) {
        for (int b = 1; b <= m + 1; ++b) {
            d[a][b] += d[a][b - 1];
        }
    }

    for (int b = 0; b <= m + 1; ++b) {
        for (int a = 1; a <= n + 1; ++a) {
            d[a][b] += d[a - 1][b];
        }
    }

    for (int a = 0; a <= n; ++a) {
        for (int b = 0; b <= m; ++b) {
            std::cout << d[a][b] << " \n"[b == m];
        }
    }

    return 0;
}