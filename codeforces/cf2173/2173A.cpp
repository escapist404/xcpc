#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    std::vector<int> c(n, 1);
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            for (int j = 0; j <= k && i + j < n; ++j) {
                c[i + j] = 0;
            }
        }
    }

    std::cout << std::count(c.begin(), c.end(), 1) << "\n";
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