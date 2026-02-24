#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

void solve() {
    int n;
    i64 k;
    std::cin >> n >> k;

    i64 f = 1;
    bool u = false;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        if (k % x == 0) {
            f = (__int128_t)f * x / std::gcd(f, x);
            u = true;
        }
        if (x == 1) {
            u = true;
        }
    }

    if (k == f && u) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
