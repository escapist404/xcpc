#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    int c[] = {0, 0, 0};
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        ++x;
        c[x]++;
    }

    std::cout << c[1] + 2 * (c[0] % 2) << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}