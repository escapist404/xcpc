#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

void solve() {
    int s, k, m;
    std::cin >> s >> k >> m;

    int t = m % (2 * k);
    if (t < k) {
        std::cout << std::max(s - t, 0) << "\n";
    } else {
        std::cout << std::max(std::min(k, s) - (t - k), 0) << "\n";
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
