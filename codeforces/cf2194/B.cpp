#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

void solve() {
    int n, x, y;
    std::cin >> n >> x >> y;

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        b[i] = a[i] / x * y;
    }

    i64 B = std::accumulate(b.begin(), b.end(), 0LL);
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = std::max(ans, a[i] + B - b[i]);
    }

    std::cout << ans << "\n";
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
