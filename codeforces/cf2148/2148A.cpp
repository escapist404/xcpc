#include <bits/stdc++.h>

void solve() {
    int n, x;
    std::cin >> x >> n;
    if (n % 2 == 0) {
        std::cout << 0 << "\n";
    } else {
        std::cout << x << "\n";
    }
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}