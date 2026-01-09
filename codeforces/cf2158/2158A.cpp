#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, y, r;
    std::cin >> n >> y >> r;
    std::cout << std::min(n, y / 2 + r) << "\n";
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
