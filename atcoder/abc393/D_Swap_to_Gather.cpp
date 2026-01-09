#include <bits/stdc++.h>

using i64 = long long;

int main() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    i64 ans = 1E18;
    int cnt = std::count(s.begin(), s.end(), '1');

    i64 lhs = 0, rhs = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            rhs += i;
        }
    }

    int res = cnt;
    for (int i = 0; i < n; ++i) {
        ans = std::min(ans, lhs + rhs - 1LL * (cnt - res) * (cnt - res - 1) / 2 - 1LL * res * (res - 1) / 2);
        lhs += cnt - res;
        res -= s[i] == '1';
        rhs -= res;
    }

    std::cout << ans << "\n";
    return 0;
}
