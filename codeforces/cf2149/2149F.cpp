#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int h, d;
    std::cin >> h >> d;

    int ans = 0, cur = 0;
    while (cur < d) {
        int l = 0, r = 1000000000;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (1LL * m * (m + 1) / 2 <= h - 1) {
                l = m;
            } else {
                r = m;
            }
        }
        int diff = std::min(d - cur, l);
        cur += diff;
        ans += diff;
        h -= 1LL * diff * (diff + 1) / 2;
        if (cur == d) {
            break;
        }
        if (h == 1) {
            ans += 2 * (d - cur);
            cur = d;
            break;
        }
        ans++;
        h++;
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}