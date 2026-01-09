#include <bits/stdc++.h>

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<int> c(n + 1);
    for (int i = 0; i < n; i++) {
        c[a[i]]++;
    }

    int mex = 0;
    while (mex < n && c[mex] > 0) {
        mex++;
    }

    --k;
    for (int i = mex - 1, &p = c[mex]; i >= 0; i--) {
        if (c[i] >= 2) {
            p += c[i];
            c[i] = 0;
            mex = i;
        }
    }

    using i64 = long long;
    if (k == 0) {
        i64 ans = 0;
        for (int i = 0; i <= n; ++i) {
            ans += 1LL * c[i] * i;
        }
        std::cout << ans << "\n";
        return;
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