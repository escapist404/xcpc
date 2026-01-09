#include <bits/stdc++.h>

void bruteforce() {
    std::string s;
    std::cin >> s;
    int n = s.size();

    int c = std::count(s.begin(), s.end(), '2');
    if (c > 31) {
        std::cout << -1 << "\n";
        return;
    }

    int ans = n;
    std::string ans_str;

    for (int S = 0; S < 1 << c; ++S) {
        std::string r;
        int j = 0;
        for (int i = 0; i < n; ++i) {
            char ch = s[i];
            if (s[i] == '2') {
                if ((S >> j) & 1) {
                    ch = '1';
                } else {
                    ch = '0';
                }
            }
            if (r.empty() == true) {
                r.push_back(ch);
            } else if (r.back() == ch) {
                r.pop_back();
            } else {
                r.push_back(ch);
            }
        }
        if ((int)r.size() < ans) {
            ans_str = r;
            ans = r.size();
        }
    }

    std::cout << ans << " " << ans_str << "\n";
}

void solve() {
    bruteforce();
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}