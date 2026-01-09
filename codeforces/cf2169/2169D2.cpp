#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    i64 x, y, k;
    std::cin >> x >> y >> k;
    k--;

    if (y == 1) {
        std::cout << -1 << "\n";
        return;
    }

    if (k < y - 1) {
        std::cout << k + 1 << "\n";
        return;
    }

    for (i64 i = 0; i < x; ) {
        i64 d = k / (y - 1);
        i64 n = (d + 1) * (y - 1);
        i64 s = (n - k) / d + ((n - k) % d > 0);
        i64 r = std::min(x - i, s);
        i += r;
        k += r * d;
    }

    if (k < 1E12) {
        std::cout << k + 1 << "\n";
    } else {
        std::cout << -1 << "\n";
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
