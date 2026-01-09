#include <bits/stdc++.h>

using i64 = long long;
const i64 INF = 2E14 + 1;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<i64> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    std::vector<std::array<i64, 2>> f(n + 1, std::array<i64, 2>({-INF, -INF}));
    for (int i = 0; i < n; ++i) {
        f[i + 1][0] = std::max(f[i][0] + a[i], a[i]);
        f[i + 1][1] = std::max({f[i][0] + a[i] + abs(b[i]), a[i] + abs(b[i]), f[i][1] + a[i], a[i]});
    }

    i64 ans = -INF;
    for (int i = 0; i < n; ++i) {
        ans = std::max(ans, f[i + 1][k % 2]);
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
