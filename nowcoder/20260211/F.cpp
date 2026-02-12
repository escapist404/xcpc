#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <queue>
#include <cassert>

using i64 = long long;

void solve() {
    int n, a, b;
    std::cin >> n >> a >> b;

    i64 ans = 0;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 8; ++j) {
            i64 all = std::max(7LL * (a + b), 8LL * a);
            int res = n - i * 8 - j * 7;
            if (res < 0) {
                continue;
            }
            ans = std::max(ans, 1LL * i * (a + b) + 1LL * j * a + res / 56 * all);
        }
    }

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 28; ++j) {
            i64 all = std::max(7LL * (a + b), 28LL * b);
            int res = n - i * 8 - j * 2;
            if (res < 0) {
                continue;
            }
            ans = std::max(ans, 1LL * i * (a + b) + 1LL * j * b + res / 56 * all);
        }
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
