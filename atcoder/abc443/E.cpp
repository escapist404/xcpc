#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>

using i64 = long long;

void solve() {
    int n, c;
    std::cin >> n >> c;
    --c;

    std::vector<int> low(n);
    std::vector<std::string> s(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
        for (int j = 0; j < n; ++j) {
            if (s[i][j] == '#') {
                low[j] = i;
            }
        }
    }

    std::vector<std::vector<int>> vis(n, std::vector<int>(n));
    vis[n - 1][c] = 1;

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < n; ++j) {
            if (vis[i][j]) {
                continue;
            }
            bool cond = false;
            cond |= (j > 0 && vis[i + 1][j - 1]);
            cond |= vis[i + 1][j];
            cond |= (j < n - 1 && vis[i + 1][j + 1]);
            if (cond) {
                if (s[i][j] == '.') {
                    vis[i][j] = 1;
                } else if (low[j] == i) {
                    for (int k = 0; k <= i; ++k) {
                        vis[k][j] = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        std::cout << vis[0][i];
    }
    std::cout << "\n";
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
