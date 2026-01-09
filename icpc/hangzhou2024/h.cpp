#include <bits/stdc++.h>

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> vis(n);
    std::vector<std::tuple<int, int, int>> c(k);

    long long sum = 0;
    for (auto& [s, l, r] : c) {
        std::cin >> l >> r;
        --l;
        s = r - l;
        sum += s;
    }

    std::sort(c.begin(), c.end(), [](auto x, auto y) {
        return std::get<1>(x) < std::get<1>(y);
    });

    bool ok = true;
    for (int i = 1; i < k; ++i) {
        if (std::get<1>(c[i]) != std::get<2>(c[i - 1])) {
            ok = false;
        }
    }

    if (ok == false || sum != n) {
        std::cout << "IMPOSSIBLE\n";
        return;
    }

    std::sort(c.begin(), c.end(), [](auto x, auto y) {
        return x > y;
    });

    if (k != 1 && std::get<0>(c.back()) == std::get<0>(c.front())) {
        std::cout << "IMPOSSIBLE\n";
        return;
    }

    if (k != 1 && std::get<0>(c[0]) == std::get<0>(c[1]) && std::get<0>(c.back()) + 1 == std::get<0>(c.front())) {
        std::cout << "IMPOSSIBLE\n";
        return;
    }

    int root = std::get<1>(c.front());
    std::vector<int> par(n);

    for (int i = 0; i < k; ++i) {
        auto [s, l, r] = c[i];
        int p = root;
        if (i == k - 1 && s + 1 != std::get<0>(c.front())) {
            p = root + 1;
        }

        for (int j = l; j < r; ++j) {
            par[j] = p;
            p = j;
        }
    }

    par[root] = -1;

    for (int i = 0; i < n; ++i) {
        std::cout << par[i] + 1 << " \n"[i == n - 1];
    }
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
