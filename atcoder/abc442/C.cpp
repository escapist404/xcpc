#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> c(n, n - 1);
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x, --y;
        c[x]--, c[y]--;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << 1LL * c[i] * (c[i] - 1) * (c[i] - 2) / 6 << " \n"[i == n - 1];
    }

    return 0;
}
