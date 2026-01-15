#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> c[i];
    }

    int ans[2] = {};
    for (int i = 0; i < n; ++i) {
        bool ok = true;
        for (int j = 0; j < n; ++j) {
            if (a[j] >= b[(j + i) % n]) {
                ok = false;
            }
        }
        ans[0] += ok;
    }

    for (int i = 0; i < n; ++i) {
        bool ok = true;
        for (int j = 0; j < n; ++j) {
            if (b[j] >= c[(j + i) % n]) {
                ok = false;
            }
        }
        ans[1] += ok;
    }

    std::cout << 1LL * ans[0] * ans[1] * n << "\n";
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
