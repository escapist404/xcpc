#include <bits/stdc++.h>

const int D = 30;

void solve() {
    int l, r;
    std::cin >> l >> r;

    long long ans = 0;
    std::vector<int> a(r - l + 1);

    for (int i = D - 1; i >= 0; --i) {
        int c = 0, d = 0;
        for (int j = l; j <= r; ++j) {
            if ((j >> i) & 1) {
                ++c;
            } else {
                ++d;
            }
        }
        ans += 1LL * (1 << i) * std::min(2 * c, r - l + 1);
        for (int j = r; j >= l; --j) {
            if ((j >> i) & 1) {
                if (d > 0) {
                    --d;
                } else {
                    a[j - l] |= 1 << i;
                }
            } else {
                if (c > 0) {
                    --c;
                    a[j - l] |= 1 << i;
                }
            }
        }
    }

    std::cout << ans << "\n";
    for (int i = 0; i < r - l + 1; ++i) {
        std::cout << a[i] << " \n"[i == r - l];
    }
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}