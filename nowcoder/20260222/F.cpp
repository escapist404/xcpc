#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <array>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> s(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }

    std::vector<int> c(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '1') {
                c[j]++;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        std::vector<std::array<int, 3>> f(m + 1);
        for (int j = 0; j < m; ++j) {
            int d = s[i][j] == '0' ? c[j] : n - c[j];
            int r = n - 1 - d;
            f[j + 1][0] = f[j][0] + d;
            f[j + 1][1] = std::min(f[j][0], f[j][1]) + r;
            f[j + 1][2] = std::min(f[j][1], f[j][2]) + d;
        }
        std::cout << std::min({f.back()[0], f.back()[1], f.back()[2]}) << "\n";
    }
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
