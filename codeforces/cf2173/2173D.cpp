#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    if (k > 30) {
        std::cout << k - 1 + __builtin_popcount(n) << "\n";
        return;
    }

    std::map<std::tuple<int, int, int>, int> g;
    auto f = [&](auto& self, int i, int x, int c) -> int {
        if (g.count({i, x, c})) {
            return g[{i, x, c}];
        }
        if (c > k) {
            return (int)1E9;
        }
        if (i >= 30) {
            int y;
            if (c < k) {
                y = 1E9;
            } else {
                y = x;
            }
            return g[{i, x, c}] = y;
        }

        int cur_x = (n >> i & 1) + x;
        int y = std::min((int)1E9, self(self, i + 1, cur_x / 2, c) + cur_x % 2);

        int cur_nx = cur_x + 1;
        y = std::min(y, self(self, i + 1, cur_nx / 2, c + 1) + cur_nx % 2);

        return g[{i, x, c}] = y;
    };

    std::cout << __builtin_popcount(n) - f(f, 0, 0, 0) + k << "\n";
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