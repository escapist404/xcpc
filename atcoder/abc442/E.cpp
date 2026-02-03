#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using i64 = long long;

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<int, int>> point(n);

    for (auto& [x, y] : point) {
        std::cin >> x >> y;
    }

    auto cross = [&](std::pair<int, int> x, std::pair<int, int> y) {
        return (1LL * x.first * y.second - 1LL * x.second * y.first);
    };

    auto cmp = [&](std::pair<int, int> x, std::pair<int, int> y) {
        bool ah = x.second > 0 || (x.second == 0 && x.first > 0);
        bool bh = y.second > 0 || (y.second == 0 && y.first > 0);
        if (ah != bh) {
            return ah < bh;
        }
        return cross(x, y) < 0;
    };

    auto sorted = point;
    std::sort(sorted.begin(), sorted.end(), cmp);

    while (q--) {
        int a, b;
        std::cin >> a >> b;
        --a, --b;
        if (cmp(point[a], point[b]) || (cross(point[a], point[b]) == 0 && 1LL * point[a].first * point[b].first + 1LL * point[a].second * point[b].second > 0)) {
            std::cout << std::upper_bound(sorted.begin(), sorted.end(), point[b], cmp) - std::lower_bound(sorted.begin(), sorted.end(), point[a], cmp) << "\n";
        } else {
            std::cout << n - (std::lower_bound(sorted.begin(), sorted.end(), point[a], cmp) - std::upper_bound(sorted.begin(), sorted.end(), point[b], cmp)) << "\n";
        }
    }

    return 0;
}
