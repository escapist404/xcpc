#include <bits/stdc++.h>

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    using i64 = long long;
    std::vector<i64> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        p[i] = p[i - 1] + a[i - 1];
    }

    int s = 0;
    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int c;
            std::cin >> c;
            s += c;
            s %= n;
        } else {
            int l, r;
            std::cin >> l >> r;
            --l;
            l += s, r += s;
            l %= n, r %= n;

            if (l < r) {
                std::cout << p[r] - p[l] << "\n";
            } else {
                std::cout << p[n] - p[l] + p[r] << "\n";
            }
        }
    }
}