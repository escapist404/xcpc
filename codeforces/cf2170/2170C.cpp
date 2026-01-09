#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    i64 k;
    std::cin >> n >> k;

    std::vector<int> q(n), r(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> q[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> r[i];
    }

    int ans = 0;
    auto qs = std::multiset<i64>(q.begin(), q.end());
    std::sort(r.begin(), r.end(), std::greater<int>());
    for (int i = 0; i < n; ++i) {
        int m = r[i] + 1;
        i64 p = (k + 1 - m) / m;
        auto it = qs.upper_bound(p);
        if (it != qs.begin()) {
            qs.erase(std::prev(it));
            ans++;
        }
    }

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
