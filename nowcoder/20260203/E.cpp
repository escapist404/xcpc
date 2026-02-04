#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n + 1);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    a[n] = k;

    int ans = -2E6;
    for (int i = 0; i <= n; ++i) {
        ans = std::max(ans, a[i] + a[(i + n) % (n + 1)]);
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
