#include <bits/stdc++.h>

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto& i : a) {
        std::cin >> i;
    }

    auto popcount = [](int x) {
        int c = 0;
        while (x) {
            if (x & 1) {
                c++;
            }
            x >>= 1;
        }
        return c;
    };

    auto len = [](int x) {
        int c = 0;
        do {
            c++;
            x >>= 1;
        } while (x);
        return c;
    };

    std::vector<std::vector<int>> p(3, std::vector<int>(n + 1));
    std::vector<int> pl(n + 1);
    for (int i = 1; i <= n; ++i) {
        int v;
        if (popcount(a[i - 1]) == 1) {
            v = 2;
        } else if (popcount(a[i - 1] >> 1) == 1) {
            v = 1;
        } else {
            v = 0;
        }

        pl[i] += pl[i - 1] + len(a[i - 1]) - 1;
        p[0][i] += p[0][i - 1];
        p[1][i] += p[1][i - 1];
        p[2][i] += p[2][i - 1];
        p[v][i]++;
    }
    
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        --l;

        int ans = pl[r] - pl[l] + (p[0][r] - p[0][l]) + (p[1][r] - p[1][l]) / 2;
        std::cout << ans << "\n";
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