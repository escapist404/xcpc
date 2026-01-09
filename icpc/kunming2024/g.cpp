#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>

using i64 = long long;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int tt;
    std::cin >> tt;
    while (tt--) {
        [&]() {
            auto gcd = [](auto& self, i64 a, i64 b) -> i64 {
                if (b == 0) {
                    return a;
                }
                return self(self, b, a % b);
            };

            i64 a, b;
            std::cin >> a >> b;

            int ans = 25;
            auto find = [&](auto& self, std::pair<i64, i64> v, int d) {
                if (d >= ans) {
                    return;
                }
                auto [a, b] = v;
                if (a == 0 && b == 0) {
                    ans = std::min(ans, d);
                    return;
                }
                i64 g = gcd(gcd, a, b);
                if (a > 0) {
                    self(self, {a - g, b}, d + 1);
                }
                if (b > 0) {
                    self(self, {a, b - g}, d + 1);
                }
            };

            find(find, {a, b}, 0);

            std::cout << ans << "\n";
        }();
    }
}
