#include <bits/stdc++.h>

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (auto& i : a) {
        std::cin >> i;
    }

    std::vector<int> d(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        d[i] = a[i] == a[i + 1];
    }

    std::vector<int> pc(n + 1);
    for (int i = 1; i <= n; ++i) {
        pc[i] = pc[i - 1] + a[i - 1];
    }

    std::vector<int> pd(n);
    for (int i = 1; i < n; ++i) {
        pd[i] = pd[i - 1] + d[i - 1];
    }

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        --l;

        if ((pc[r] - pc[l]) % 3 != 0 || (r - l) % 3 != 0) {
            std::cout << "-1\n";
            continue;
        }

        std::cout << ((r - l) / 3 + ((pd[r - 1] - pd[l]) > 0)) << "\n";
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