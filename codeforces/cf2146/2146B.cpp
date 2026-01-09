#include <bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> s(n);
    for (int i = 0; i < n; ++i) {
        int l;
        std::cin >> l;
        s[i].resize(l);
        for (int j = 0; j < l; ++j) {
            std::cin >> s[i][j];
            --s[i][j];
        }
    }

    std::vector<int> cnt(m);
    int zero = m;
    for (int i = 0; i < n; ++i) {
        for (const auto& j : s[i]) {
            if (cnt[j] == 0) {
                --zero;
            }
            cnt[j]++;
        }
    }

    int ans = zero == 0;
    for (int i = 0; i < n; ++i) {
        for (const auto& j : s[i]) {
            cnt[j]--;
            if (cnt[j] == 0) {
                ++zero;
            }
        }
        if (zero == 0) {
            ++ans;
        }
        for (const auto& j : s[i]) {
            if (cnt[j] == 0) {
                --zero;
            }
            cnt[j]++;
        }
    }

    if (ans >= 3) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}