#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q, s;
    std::cin >> n >> q >> s;

    std::vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> t[i];
    }

    std::vector<int> pt(n + 1);
    for (int i = 1; i <= n; ++i) {
        pt[i] = pt[i - 1] + t[i - 1];
    }

    for (int i = 0; i < q; ++i) {
        int x, y;
        std::cin >> x >> y;

        std::cout << s + pt[x - 1] + y - 1 << "\n";
    }

    return 0;
}
