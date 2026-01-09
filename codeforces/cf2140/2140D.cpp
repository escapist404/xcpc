#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;
            std::vector<std::pair<int, int>> a(n);

            using i64 = long long;
            i64 ans = 0;
            for (int i = 0; i < n; ++i) {
                int l, r;
                std::cin >> l >> r;
                a[i] = {l, r};
                ans += r - l;
            }

            std::sort(a.begin(), a.end(), [](auto x, auto y) {
                if (x.first + x.second != y.first + y.second) {
                    return x.first + x.second > y.first + y.second;
                } else {
                    return x.first > y.first;
                }
            });

            if (n % 2 == 0) {
                for (int i = 0; i < n / 2; ++i) {
                    ans += a[i].second;
                }
                for (int i = n / 2; i < n; ++i) {
                    ans -= a[i].first;
                }
            } else {
                i64 split1 = 0, split2 = 0, old = ans;
                for (int i = 0; i < n / 2; ++i) {
                    split1 += a[i].second;
                }
                for (int i = n / 2 + 1; i < n; ++i) {
                    split2 -= a[i].first;
                }
                ans = split1 + split2 + old;
                for (int i = 0; i < n / 2; ++i) {
                    ans = std::max(ans, split1 - a[i].second + a[n / 2].second + split2 + old);
                }
                for (int i = n / 2 + 1; i < n; ++i) {
                    ans = std::max(ans, split2 + a[i].first - a[n / 2].first + split1 + old);
                }
            }

            std::cout << ans << "\n";
        }();
    }
}