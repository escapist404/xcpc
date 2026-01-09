#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    bool ok = true;
    std::vector<int> p(n);
    for (int i = 0, len; i < n && ok; i += len) {
        len = 1;
        if (s[i] == '1') {
            p[i] = i;
            continue;
        }
        while (i + len < n && s[i + len] == s[i]) {
            ++len;
        }
        if (len == 1) {
            ok = false;
        } else {
            for (int j = i; j < i + len - 1; ++j) {
                p[j] = j + 1;
            }
            p[i + len - 1] = i;
        }
    }

    if (ok == true) {
        std::cout << "YES\n";
        for (int i = 0; i < n; ++i) {
            std::cout << p[i] + 1 << " \n"[i == n - 1];
        }
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