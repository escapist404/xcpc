#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::string s, t;
    std::cin >> s >> t;

    auto compute = [&](std::string s) {
        std::vector<std::pair<int, int>> op;
        auto it = std::adjacent_find(s.begin(), s.end());
        if (it == s.end()) {
            op.emplace_back(1, 3);
            for (int i = 0; i < 3; ++i) {
                s[i] = s[i] ^ 1;
            }
        }

        while (true) {
            if (std::count(s.begin(), s.end(), '0') == n) {
                break;
            }
            int pos = -1, len;
            for (int i = 0, j; i < n; i += j) {
                j = 0;
                while (i + j < n && s[i + j] == s[i]) {
                    ++j;
                }
                if (pos == -1 || j > len) {
                    pos = i;
                    len = j;
                }
            }
            op.emplace_back(pos + 1, pos + len);
            for (int i = pos; i < pos + len; ++i) {
                s[i] = s[i] ^ 1;
            }
        }

        return op;
    };

    auto x = compute(s);
    auto y = compute(t);
    x.insert(x.end(), y.rbegin(), y.rend());

    std::cout << x.size() << "\n";
    for (auto [l, r] : x) {
        std::cout << l << " " << r << "\n";
    }
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
