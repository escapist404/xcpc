#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;

            using i64 = long long;
            std::vector<int> a(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> a[i];
            }

            i64 delta[] = {0, 0}, most[] = {(i64)1e18, (i64)-1e18}, ans = 0;
            for (int i = 0; i < n; ++i) {
                int sign = i & 1;
                if (sign == 0) {
                    ans += a[i];
                    delta[0] = std::max(delta[0], -2LL * a[i] + i + most[1]);
                    most[0] = std::min(most[0], 2LL * a[i] + i);
                } else {
                    ans -= a[i];
                    delta[1] = std::max(delta[1], 2LL * a[i] + i - most[0]);
                    most[1] = std::max(most[1], 2LL * a[i] - i);
                }
            }

            ans += std::max({delta[0], delta[1], 1LL * (n - 1) / 2 * 2});
            std::cout << ans << "\n";
        }();
    }
}
