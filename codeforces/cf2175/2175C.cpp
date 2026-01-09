#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s, t;
    std::cin >> s >> t;

    int n = s.size(), m = t.size();

    int c[26];
    for (int i = 0; i < 26; ++i) {
        c[i] = std::count(t.begin(), t.end(), 'a' + i);
    }

    int d[26];
    for (int i = 0; i < 26; ++i) {
        d[i] = std::count(s.begin(), s.end(), 'a' + i);
    }

    for (int i = 0; i < 26; ++i) {
        if (c[i] < d[i]) {
            std::cout << "Impossible\n";
            return;
        }
    }

    std::string ans;
    int p = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 26; ++j) {
            int v = p != n && s[p] == 'a' + j;
            if (c[j] - 1 >= d[j] - v) {
                ans.push_back('a' + j);
                c[j]--;
                if (s[p] == 'a' + j) {
                    p++;
                    d[j]--;
                }
                break;
            }
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