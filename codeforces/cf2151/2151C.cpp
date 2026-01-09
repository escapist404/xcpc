#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::deque<int> a(2 * n);

    using i64 = long long;
    for (int i = 0; i < 2 * n; ++i) {
        std::cin >> a[i];
    }

    i64 ans0 = 0, ans1 = 0, ans2 = 0;
    for (int i = 1; i < 2 * n; i += 2) {
        ans1 += a[i] - a[i - 1];
        ans2 += a[i - 1] - a[i];
    }

    std::cout << ans1 << " \n"[n == 1];
    for (int k = 2; k <= n; ++k) {
        ans0 += a.back() - a.front();
        ans1 -= a.back() - a.front();
        ans2 -= a.front() - a.back();
        a.pop_back();
        a.pop_front();
        std::cout << ans0 + std::max(ans1, ans2) << " \n"[k == n];
        std::swap(ans1, ans2);
    }
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}