#include <bits/stdc++.h>

void solve() {
    int k, x;
    std::cin >> k >> x;
    while (k > 0) {
        x *= 2;
        --k;
    }

    std::cout << x << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}