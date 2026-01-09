#include <bits/stdc++.h>

const int D = 30;

void solve() {
    int l, r;
    std::cin >> l >> r;

    long long ans = 0;
    std::vector<int> a(r - l + 1);

    for (int i = D - 1; i >= 0; --i) {
        int c = 0, d = 0;
        std::vector<int> one, zero;
        for (int j = l; j <= r; ++j) {
            if ((j >> i) & 1) {
                ++c;
                // if (a[j - l] < l) {
                //     --c;
                //     a[j - l] |= 1 << i;
                //     continue;
                // }
                a[j - l] |= 1 << i;
                one.push_back(j);
            } else {
                ++d;
                // if ((a[j - l] | (1 << i)) > r) {
                //     --d;
                //     continue;
                // }
                zero.push_back(j);
            }
        }
        for (int j = 0; j < (int)zero.size() && j < c; ++j) {
            // if ((a[zero[j] - l] ^ (1 << i)) > r) {
            //     continue;
            //     ++c;
            // }
            a[zero[j] - l] ^= 1 << i;
        }
        for (int j = 0; j < (int)one.size() && j < d; ++j) {
            // if (a[one[j] - l] ^ (1 << i) < l) {
            //     continue;
            //     ++d;
            // }
            a[one[j] - l] ^= 1 << i;
        }
    }

    for (int i = 0; i < r - l + 1; ++i) {
        ans += (i + l) | a[i];
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