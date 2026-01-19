#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

void solve() {
    int n, k;
    std::cin >> n >> k;
    if (k > n) {
        std::cout << "-1\n";
    } else {
        int ans = 0;
        while (std::__lg(n) > std::__lg(k)) {
            n /= 2;
            ++ans;
        }
        if (n > k) {
            std::cout << "-1\n";
        } else {
            std::cout << ans << "\n";
        }
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
