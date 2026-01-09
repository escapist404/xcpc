#include <bits/stdc++.h>

void solve() {
    int x, y, z;
    std::cin >> x >> y >> z;
    
    for (int i = 0; i < 31; ++i) {
        int u = (x >> i) & 1;
        int v = (y >> i) & 1;
        int w = (z >> i) & 1;

        if (u + v + w == 2) {
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES\n";
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