#include <bits/stdc++.h>

void solve() {
    using i64 = long long;
    i64 a, b;
    std::cin >> a >> b;

    if (a % 2 == 0 && b % 2 != 0) {
        std::cout << "-1\n";
    } else if (a % 2 != 0 && b % 2 == 0 && b % 4 != 0) {
        std::cout << "-1\n";
    } else {
        a *= b;
        b = 1;
        if (a % 4 == 0) {
            a /= 2;
            b *= 2;
        }
        std::cout << a + b << "\n";
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