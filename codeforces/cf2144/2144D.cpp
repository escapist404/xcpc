#include <bits/stdc++.h>

using i64 = long long;
const int M = 200'000;

void solve();

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}

void solve() {
    int n, y;
    std::cin >> n >> y;

    std::vector<int> c(M + 1);
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        c[v]++;
    }

    auto p = c;
    for (int i = 1; i <= M; ++i) {
        p[i] += p[i - 1];
    }

    i64 ans = -1e18;
    for (int x = 2; x <= M; ++x) {
        i64 cur = 0;
        for (int i = 1; i <= M / x + (M % x > 0); ++i) {
            int l = (i - 1) * x;
            int r = std::min(i * x, M);
            cur += 1LL * i * (p[r] - p[l]);
            cur -= 1LL * (p[r] - p[l]) * y;
            cur += 1LL * std::min(p[r] - p[l], c[i]) * y;
        }
        ans = std::max(ans, cur);
    }

    std::cout << ans << "\n";
}
