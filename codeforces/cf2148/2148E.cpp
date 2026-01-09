#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        --a[i];
    }

    std::vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        cnt[a[i]]++;
    }
    for (int i = 0; i < n; ++i) {
        if (cnt[i] % k != 0) {
            std::cout << "0\n";
            return;
        }
    }

    i64 ans = 0;
    std::vector<int> occ(n);
    for (int i = 0, last = 0; i < n; ++i) {
        occ[a[i]]++;
        if (occ[a[i]] > cnt[a[i]] / k) {
            while (a[last] != a[i]) {
                occ[a[last]]--;
                last++;
            }
            occ[a[last]]--;
            last++;
        }
        ans += (i - last + 1);
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}