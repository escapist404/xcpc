#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> p(2 * n, 1);

    for (int i = n; i >= 2; i -= 2) {
        p[(n - i) / 2] = p[(n - i) / 2 + i] = i;
    }

    for (int i = n - 3; i >= 2; i -= 2) {
        p[n + 1 + (n - 3 - i) / 2] = p[n + 1 + (n - 3 - i) / 2 + i] = i;
    }

    if (n - 1 > 1) {
        p[(n + 1) / 2] = p[(n + 1) / 2 + n - 1] = n - 1;
    }

    for (int i = 0; i < 2 * n; ++i) {
        std::cout << p[i] << " \n"[i == 2 * n - 1];
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