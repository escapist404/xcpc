#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    std::vector<std::vector<int>> b(n, std::vector<int>(m));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> b[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x1 = i;
            int x2 = n - 1 - i;
            int y1 = j;
            int y2 = m - 1 - j;
            int r1 = a[x1][y1] ^ a[x1][y2] ^ a[x2][y1] ^ a[x2][y2];
            int r2 = b[x1][y1] ^ b[x1][y2] ^ b[x2][y1] ^ b[x2][y2];
            if (r1 != r2) {
                std::cout << "No\n";
                return;
            }
        }
    }

    std::cout << "Yes\n";
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
