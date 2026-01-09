#include <bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;

    int max = 0;
    bool ok = false;
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        if (max >= x) {
            ok = true;
        }
        max = std::max(max, x);
    }

    if (ok == false) {
        std::cout << n - max + 1 << "\n";
    } else {
        std::cout << "1\n";
    }
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}