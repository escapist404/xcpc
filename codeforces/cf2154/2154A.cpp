#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    int c = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1' && c == 0) {
            ans++;
        }
        c += s[i] == '1';
        if (i >= k - 1) {
            c -= s[i - k + 1] == '1';
        }
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