#include <bits/stdc++.h>

void solve() {
    using i64 = long long;
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i].first;
        b[i].second = i;
    }

    std::sort(b.begin(), b.end());

    for (int i = 0, s, c = 1; i < n; i += s) {
        int j = i + b[i].first;
        s = b[i].first;
        if (j > n) {
            std::cout << "-1\n";
            return;
        } else {
            if (b[j - 1].first != b[i].first) {
                std::cout << "-1\n";
                return;
            }
            for (int k = i; k < j; ++k) {
                b[k].first = c;
            }
            c++;
        }
    }

    std::sort(b.begin(), b.end(), [](auto x, auto y) {
        return x.second < y.second;
    });

    for (int i = 0; i < n; ++i) {
        std::cout << b[i].first << " \n"[i == n - 1];
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