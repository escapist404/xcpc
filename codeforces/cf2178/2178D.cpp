#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    if (m > n / 2) {
        std::cout << "-1\n";
        return;
    }

    std::vector<int> id(n);
    std::iota(id.begin(), id.end(), 0);
    std::sort(id.begin(), id.end(), [&](int x, int y) {
        return a[x] < a[y];
    });

    std::vector<std::pair<int, int>> ans;
    if (m == 0) {
        bool ok = true;
        int p = n - 2;
        i64 sum = 0;
        while (p >= 0 && sum < a[id[n - 1]]) {
            sum += a[id[p--]];
        }
        if (sum < a[id[n - 1]]) {
            std::cout << "-1\n";
            return;
        }
        for (int i = 0; i <= p; ++i) {
            ans.emplace_back(id[i], id[i + 1]);
        }
        for (int i = p + 1; i < n - 1; ++i) {
            ans.emplace_back(id[i], id[n - 1]);
        }
    } else {
        for (int i = 0; i < m - 1; ++i) {
            ans.emplace_back(id[2 * i + 1], id[2 * i]);
        }
        for (int i = 2 * (m - 1); i < n - 1; ++i) {
            ans.emplace_back(id[i + 1], id[i]);
        }
    }

    std::cout << ans.size() << "\n";
    for (auto [x, y] : ans) {
        std::cout << x + 1 << " " << y + 1 << "\n";
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
