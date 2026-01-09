#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> cur(16);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        for (int j = 0; j < 16; ++j) {
            cur[j] += x % 10;
            x /= 10;
        }
    }

    i64 ans = 0;
    for (int i = 0; i < 15; ++i) {
        ans += cur[i] / 10;
        cur[i + 1] += cur[i] / 10;
    }

    std::cout << ans << "\n";
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}