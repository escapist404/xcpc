#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<i64> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    if (std::count(a.begin(), a.end(), 1) == n) {
        std::cout << n << "\n";
        return;
    }

    int ans = 0;
    if (a[0] == 1) {
        a[0] = *std::find_if(a.begin(), a.end(), [](auto v) { return v != 1LL; });
        ++ans;
    }

    if (a[n - 1] == 1) {
        a[n - 1] = *std::find_if(a.rbegin(), a.rend(), [](auto v) { return v != 1LL; });
        ++ans;
    }

    for (int i = 1; i < n - 1; ++i) {
        if (a[i] == 1) {
            a[i] = a[i - 1] * a[i + 1];
            ++ans;
        }
    }

    int cur = 0;
    for (int i = 1; i < n; ++i) {
        if (std::gcd(a[i - 1], a[i]) == 1) {
            cur++;
        } else {
            ans += (cur + 1) / 2;
            cur = 0;
        }
    }
    ans += (cur + 1) / 2;

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
