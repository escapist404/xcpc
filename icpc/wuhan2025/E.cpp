#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> s(n), t(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> t[i];
    }

    std::sort(s.begin(), s.end());
    std::sort(t.begin(), t.end());

    bool flag_s = false, flag_t = false;
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] + 1 == s[i + 1]) {
            flag_s = true;
        }
        if (t[i] + 1 == t[i + 1]) {
            flag_t = true;
        }
    }

    if (flag_s != flag_t) {
        std::cout << "No\n";
    } else {
        if (flag_s) {
            if (std::count_if(s.begin(), s.end(), [](int x) { return x & 1; }) == std::count_if(t.begin(), t.end(), [](int x) { return x & 1; })) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        } else {
            if (s == t) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
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
