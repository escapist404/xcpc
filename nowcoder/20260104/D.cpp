#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::string a, b;
    std::cin >> a >> b;
    
    if (std::count(a.begin(), a.end(), '1') % 2 != std::count(b.begin(), b.end(), '1') % 2) {
        std::cout << "NO\n";
        return;
    }

    int p = 0, c = 0;
    for (int i = 0; i < m; ++i) {
        int d = c;
        if (p == n && i < m) {
            std::cout << "NO\n";
            return;
        }
        do {
            d ^= a[p] - '0';
            ++p;
        } while (p < n && (d ^ c) != b[i] - '0');
    }

    std::cout << "YES\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
