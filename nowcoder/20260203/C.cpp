#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int max = *std::max_element(a.begin(), a.end());
    std::cout << a.front() + a.back() + 1LL * (n - 2) * max << "\n";
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
