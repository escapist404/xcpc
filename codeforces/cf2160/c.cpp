#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    int c = [](int n) {
        int c = 1;
        n >>= 1;
        while (n) {
            c++;
            n >>= 1;
        }
        return c;
    }(n);

    std::string s;
    s.resize(c);

    for (int i = 0; i < c; ++i) {
        s[i] = '0' + ((n >> i) & 1);
    }
    s.append(c, '0');

    bool ok = false;
    for (int i = c / 2; i < c; ++i) {
        if (s[i] == '1') {
            continue;
        }
        bool now = true;
        for (int j = 1; j <= i; ++j) {
            if (s[i - j] != s[i + j]) {
                now = false;
            }
        }
        if (now == true) {
            ok = true;
        }
    }

    for (int i = (c + 1) / 2 - 1; i < c; ++i) {
        bool now = true;
        for (int j = 0; j <= i; ++j) {
            if (s[i - j] != s[i + j + 1]) {
                now = false;
            }
        }
        if (now == true) {
            ok = true;
        }
    }

    if (ok == true) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
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