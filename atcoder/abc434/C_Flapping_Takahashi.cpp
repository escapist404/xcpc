#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int N, H;
    std::cin >> N >> H;

    int lo = H, hi = H;
    bool ok = true;
    for (int i = 0, s = 0; i < N; ++i) {
        int t, l, u;
        std::cin >> t >> l >> u;

        int nlo = std::max(lo - (t - s), 1);
        int nhi = hi + (t - s);

        if (nlo > u || nhi < l) {
            ok = false;
        }

        lo = std::max(nlo, l);
        hi = std::min(nhi, u);

        s = t;
    }

    if (ok) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
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
