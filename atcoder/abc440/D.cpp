#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::sort(a.begin(), a.end());
    for (int i = 0; i < q; ++i) {
        int x, y;
        std::cin >> x >> y;
        --y;

        int ix = std::lower_bound(a.begin(), a.end(), x) - a.begin();
        int cl = x;
        int cr = 2E9 + 1;

        while (cr - cl > 1) {
            int c = cl + (cr - cl) / 2;
            int ic = std::lower_bound(a.begin(), a.end(), c) - a.begin();
            int d = ic - ix;
            if (c - x - d > y) {
                cr = c;
            } else {
                cl = c;
            }
        }

        std::cout << cl << "\n";
    }
}
