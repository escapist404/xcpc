#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128_t;

i128 power(i64 base, i64 exp) {
    i128 ret = 1;
    while (exp) {
        if (exp & 1) {
            ret *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return ret;
}

void solve() {
    i64 n;
    int k;
    std::cin >> n >> k;

    i64 ans = 0;
    for (i64 a = 1; a <= 1000; ++a) {
        for (i64 b = 1; b < a; ++b) {
            if (power(a, k) - power(b, k) == n) {
                ++ans;
            }
        }
    }

    std::cout << ans << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}