#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = i * n + j + 1;
        }
    }

    int max = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int cur = a[i][j];
            if (i > 0) {
                cur += a[i - 1][j];
            }
            if (i < n - 1) {
                cur += a[i + 1][j];
            }
            if (j > 0) {
                cur += a[i][j - 1];
            }
            if (j < n - 1) {
                cur += a[i][j + 1];
            }
            max = std::max(max, cur);
        }
    }

    std::cout << max << "\n";
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
