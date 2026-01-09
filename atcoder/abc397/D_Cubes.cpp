#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using i64 = long long;

int main() {
    i64 n;
    std::cin >> n;

    for (i64 d = 1; d * d * d <= n; ++d) {
        if (n % d != 0) {
            continue;
        }
        i64 a = 3, b = 3 * d, c = d * d - n / d;
        i64 l = 1, r = 1e9;

        while (l + 1 < r) {
            i64 m = (l + r) / 2;
            if (a * m * m + b * m + c <= 0) {
                l = m;
            } else {
                r = m;
            }
        }

        if (a * l * l + b * l + c == 0) {
            std::cout << l + d << " " << l << "\n";
            return 0;
        }
    }

    std::cout << -1 << "\n";
    return 0;
}
