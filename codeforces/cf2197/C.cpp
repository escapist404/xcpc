#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

void solve() {
    i64 p, q;
    std::cin >> p >> q;

    if (3 * p - 2 * q >= 0 && q > p) {
        std::cout << "Bob\n";
    } else {
        std::cout << "Alice\n";
    }
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