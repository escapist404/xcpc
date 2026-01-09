#include <bits/stdc++.h>

const std::string u = "nanjing";

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    if (n < 7) {
        std::cout << "0\n";
        return;
    }

    int cur = 0, ans = 0;
    for (int i = 0; i <= n - 7; ++i) {
        if (s.substr(i, 7) == u) {
            cur++;
        }
    }

    ans = cur;
    std::string t = s.substr(n - 6);
    s += s.substr(0, 6);
    for (int i = 0; i < n && i < k; ++i) {
        t.push_back(s[i]);
        if (t.substr(i) == u) {
            ++cur;
        }
        if (s.substr(i, 7) == u) {
            --cur;
        }
        ans = std::max(ans, cur);
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}