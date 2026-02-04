#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

const int P = 998244353;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    int m = *std::min_element(b.begin(), b.end());
    int c = std::count_if(a.begin(), a.end(), [m](int x) { return x > m; });

    int ans = 1;
    for (int i = 1; i <= c; ++i) {
        ans = 1LL * ans * i % P;
    }
    for (int i = 1; i <= n - c; ++i) {
        ans = 1LL * ans * i % P;
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
