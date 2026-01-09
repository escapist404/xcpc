#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<std::array<int, 2>> f(n + 1);
    f[0] = {1, 1};
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') {
            if (i >= 1 && s[i - 1] == '0') {
                f[i + 1][0] = f[i - 1][0] | f[i - 1][1];
            } else if (i >= 2 && s[i - 1] == '1' && s[i - 2] == '0') {
                f[i + 1][0] = f[i - 2][0] | f[i - 2][1];
            }
        } else {
            f[i + 1] = f[i];
        }
    }

    if (f[n][0] | f[n][1]) {
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
    return 0;
}