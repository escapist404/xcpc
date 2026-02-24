#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    i64 s = std::accumulate(a.begin(), a.end(), 0LL);
    int c = std::count_if(a.begin(), a.end(), [](auto v) { return v % 2 == 1; });

    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] % 2 == 1) {
            ans += s - a[i] + 1LL * (n - c) * (a[i] - 1) + 1LL * (c - 1) * a[i];
        } else {
            ans += s - a[i] + 1LL * (n - 1) * a[i] - c;
        }
    }

    ans /= 4;
    std::cout << ans << "\n";
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
