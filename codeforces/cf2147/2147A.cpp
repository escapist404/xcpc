#include <bits/stdc++.h>

void solve() {
    int x, y;
    std::cin >> x >> y;
    if (x == y || x == y + 1) {
        std::cout << -1 << "\n";
    } else {
        if (x < y) {
            std::cout << 2 << "\n";
        } else if (y != 1) {
            std::cout << 3 << "\n";
        } else {
            std::cout << -1 << "\n";
        }
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