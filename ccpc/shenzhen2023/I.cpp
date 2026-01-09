#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128_t;

i128 power(i128 base, int exp) {
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

i128 safe_root(i128 base, int root) {
    i128 l = 1, r = powl(base, 1.0 / root) + 1;
    while (l < r - 1) {
        i64 m = (l + r) / 2;
        if (power(m, root) <= (i128)base) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

i64 uppdiv(i64 a, i64 b) {
    return a / b + (a % b > 0);
}

/*
1
592570256192463681 4
*/

void solve() {
    i64 n;
    int k;
    std::cin >> n >> k;

    i64 u = safe_root(n, k);

    i64 ans = 0;
    for (i64 d = 1; d <= u; ++d) {
        if (n % d != 0) {
            continue;
        }
        i128 l = 1;
        i128 r = safe_root(1E36, k) + 1;
        while (l < r - 1) {
            i128 m = (l + r) / 2;
            if (power(m + d, k) - power(m, k) <= (i128)n) {
                l = m;
            } else {
                r = m;
            }
        }
        if (power(l + d, k) - power(l, k) == (i128)n) {
            ++ans;
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