#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::map<int, int> v;
    for (int i = 0; i < 2 * n; ++i) {
        int x;
        std::cin >> x;
        v[x]++;
    }

    int ans = 0, flip = 0, single = 0;
    for (auto [x, c] : v) {
        if (c % 2 == 1) {
            ++ans;
            ++single;
        } else if (c % 4 == 0) {
            flip++;
        } else {
            ans += 2;
        }
    }

    ans += flip / 2 * 4;
    if (single > 0) {
        ans += flip % 2 * 2;
    }

    std::cout << ans << "\n";
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
