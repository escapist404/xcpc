#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    int max = 0, maxc = 0;
    std::vector<i64> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        int cur = std::__lg(a[i]);
        if (max < cur) {
            max = cur;
            maxc = 0;
        }
        if (max == cur) {
            ++maxc;
        }
    }

    if (maxc & 1) {
        std::cout << std::accumulate(a.begin(), a.end(), 0LL, [](i64 x, i64 y) { return x ^ y; }) << "\n";
    } else {
        i64 ans_xor = 0;
        i64 v[60]{};
        for (auto i : a) {
            for (int j = 59; j >= 0; --j) {
                if (i >> j & 1) {
                    if (v[j] == 0) {
                        v[j] = i;
                    }
                    i ^= v[j];
                }
            }
        }
        for (int i = 59; i >= 0; --i) {
            ans_xor = std::max(ans_xor, ans_xor ^ v[i]);
        }

        i64 ans_all = std::accumulate(a.begin(), a.end(), 0LL, [](i64 x, i64 y) { return x ^ y; });
        std::cout << (ans_xor & (ans_all ^ ans_xor)) << "\n";
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
