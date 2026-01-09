#include <bits/stdc++.h>

void solve() {
    int n, f;
    std::cin >> n >> f;

    std::vector<std::tuple<int, int, int>> seg(n);
    int c = 0;
    for (auto& [l, r, i] : seg) {
        std::cin >> l >> r;
        i = c++;
    }

    std::sort(seg.begin(), seg.end());

    using i64 = long long;
    i64 ans = 0;
    std::vector<int> ord, vis(n);
    c = 0;
    for (auto [l, r, i] : seg) {
        ans += r - l;
        if (r > f) {
            ord.push_back(i);
            vis[i] = 1;
            ans += std::max(l - f, 0);
            f = r;
        }
        ++c;
    }

    for (int i = n - 1; i >= 0; --i) {
        if (vis[std::get<2>(seg[i])] == 0) {
            ord.push_back(std::get<2>(seg[i]));
        }
    }

    std::cout << ans << "\n";

    for (int i = 0; i < n; ++i) {
        std::cout << ord[i] + 1 << " \n"[i == n - 1];
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