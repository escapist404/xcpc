#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

const int P = 1'000'000'007;

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, m, k;
            std::cin >> n >> m >> k;
            std::vector<int> c(k);
            for (int i = 0; i < k; ++i) {
                std::cin >> c[i];
                --c[i];
            }

            if (m == 1) {
                std::cout << 1 << "\n";
                return;
            }

            auto remove_bit = [](int val, int pos) -> int {
                int low = val & ((1LL << pos) - 1);
                int high = (val >> (pos + 1)) << pos;
                return low ^ high;
            };

            std::vector<std::vector<std::vector<bool>>> f(n + 1, std::vector<std::vector<bool>>(2));
            f[1][0] = f[1][1] = std::vector<bool>(2);
            f[1][0][0] = f[1][1][0] = 0, f[1][0][1] = f[1][1][1] = 1;

            for (int i = 2; i <= n; ++i) {
                f[i][0] = f[i][1] = std::vector<bool>(1 << i);
                for (int stat = 0; stat < 1 << i; ++stat) {
                    bool ans0 = 0, ans1 = 1;
                    for (int p : c) {
                        if (p >= i) {
                            break;
                        }
                        ans0 |= f[i - 1][1][remove_bit(stat, p)];
                        ans1 &= f[i - 1][0][remove_bit(stat, p)];
                    }
                    f[i][0][stat] = ans0;
                    f[i][1][stat] = ans1;
                }
            }

            int ans = 0;
            for (int stat = 0; stat < 1 << n; ++stat) {
                (ans += 1 + f[n][0][stat]) %= P;
            }

            std::cout << ans << "\n";
        }();
    }
    return 0;
}
