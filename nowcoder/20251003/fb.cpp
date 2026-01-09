#include <bits/stdc++.h>

void solve() {
    int n, m, p, x, a, b, c;
    std::cin >> n >> m >> p >> x >> a >> b >> c;

    std::vector<int> s(n);
    std::vector<int> t(m);

    std::for_each(s.begin(), s.end(), [&x, a, b, c, p](int& v) {
        v = x = (1LL * a * x % p * x % p + 1LL * b * x % p + c) % p;
    });
    std::for_each(t.begin(), t.end(), [&x, a, b, c, p](int& v) {
        v = x = (1LL * a * x % p * x % p + 1LL * b * x % p + c) % p;
    });

    std::vector<std::vector<int>> f(n + 1, std::vector<int>(m + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i] == t[j]) {
                f[i + 1][j + 1] = f[i][j] + 1;
            } else {
                f[i + 1][j + 1] = std::max(f[i][j + 1], f[i + 1][j]);
            }
        }
    }

    std::cout << f[n][m] << "\n";
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}