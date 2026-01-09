#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using i64 = long long;

int main() {
    // int tt;
    // std::cin >> tt;
    // while (tt--) {
    //     []() {
    //         i64 n, k;
    //         std::cin >> n >> k;

    //         auto f = [&](auto& self, const i64 c) -> i64 {
    //             if (c == 1) return 0;
    //             i64 r = self(self, c - c / k - (c % k > 0));
    //             return r / (k - 1) + 1 + r;
    //         };

    //         std::cout << f(f, n) + 1 << "\n";
    //     }();
    // }

    i64 k = 4;

    auto f = [&](auto& self, const i64 c) -> i64 {
        if (c == 1) return 0;
        i64 r = self(self, c - c / k - (c % k > 0));
        return r / (k - 1) + 1 + r;
    };

    for (int i = 1, v = 1; i <= 5; ++i) {
        std::cout << v << " " << f(f, v) + 1 << "\n";
        v *= k;
    }
    // 1 2 3 5 8 12 18 27 41 62 93
}
