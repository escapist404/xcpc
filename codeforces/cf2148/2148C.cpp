#include <bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> r(n + 1);
    for (int i = 1; i <= n; ++i) {
        int a, b;
        std::cin >> a >> b;
        r[i] = {a, b};
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int b = r[i].first - r[i - 1].first;
        if (r[i - 1].second != r[i].second) {
            if (b % 2 == 0) {
                --b;
            }
            ans += b;
        } else {
            if (b % 2 == 1) {
                --b;
            }
            ans += b;
        }
    }
    ans += m - r.back().first;

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}