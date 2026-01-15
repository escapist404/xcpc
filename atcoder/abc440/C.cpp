#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

void solve() {
    int n, w;
    std::cin >> n >> w;

    std::vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> c[i];
    }

    std::vector<i64> s(2 * w);
    for (int i = 0; i < n; ++i) {
        s[(i + 1) % (2 * w)] += c[i];
    }

    i64 cur = std::accumulate(s.begin(), s.begin() + w, 0LL);
    i64 ans = 1E18;
    for (int x = 0; x < 2 * w; ++x) {
        ans = std::min(cur, ans);
        cur -= s[(3 * w - 1 - x) % (2 * w)];
        cur += s[(4 * w - 1 - x) % (2 * w)];
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}
