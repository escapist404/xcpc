#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;

    int n = s.size();
    int ans = 0;
    if (s[0] == 'u') {
        s[0] = 's';
        ++ans;
    }
    if (s[n - 1] == 'u') {
        s[n - 1] = 's';
        ++ans;
    }

    for (int i = 0, j = 1; i < n; i += j) {
        j = 1;
        if (s[i] == 's') {
            continue;
        }
        while (i + j < n && s[i + j] == 'u') {
            ++j;
        }
        ans += j / 2;
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
