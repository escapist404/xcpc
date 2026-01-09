#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    i64 ans = 0;
    for (int i = 0, j; i < n; i += j) {
        j = 1;
        if (a[i] == 0) {
            continue;
        }
        while (i + j < n && a[i + j] > 0) {
            ++j;
        }
        ans += *std::min_element(a.begin() + i, a.begin() + i + j);
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
