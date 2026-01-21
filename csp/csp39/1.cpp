#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iomanip>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, a;
    std::cin >> n >> a;

    int m = 0;
    for (int i = 0; i < n; ++i) {
        double x, y;
        std::cin >> x >> y;

        if (x * x + y * y <= a * a) {
            ++m;
        }
    }

    std::cout << std::fixed << std::setprecision(6) << 1.0 * 4 * m / n << "\n";

    return 0;
}