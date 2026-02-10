#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(1 << n);
    for (int b = n - 1; b >= 0; --b) {
        for (int i = 0, t = 0; i < 1 << n; i += 1 << b, t++) {
            for (int j = 0; j < 1 << b; ++j) {
                a[i + j] += ((t & 1) ^ ((t >> 1) & 1)) << b;
            }
        }
    }

    for (int i = 0; i < 1 << n; ++i) {
        std::cout << a[i] << " \n"[i == (1 << n) - 1];
    }

    return 0;
}
