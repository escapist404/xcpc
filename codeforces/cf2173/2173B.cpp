#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    i64 lo = 0, hi = 0;
    for (int i = 0; i < n; ++i) {
        i64 nlo = std::min(lo - a[i], b[i] - hi);
        i64 nhi = std::max(hi - a[i], b[i] - lo);
        lo = nlo;
        hi = nhi;
    }

    std::cout << hi << "\n";
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