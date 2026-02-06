#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> a[i][j];
        }
    }

    std::vector<int> ans(n);
    bool ok = false;
    while (ok == false) {
        ok = true;
        for (int i = 0; i < n; ++i) {
            if (std::accumulate(a[i].begin(), a[i].end(), 0) < 0) {
                ok = false;
                ans[i] ^= 1;
                for (int j = 0; j < n; ++j) {
                    a[i][j] = -a[i][j];
                    a[j][i] = -a[j][i];
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        std::cout << (char)('X' + ans[i]);
    }
    std::cout << "\n";
    return 0;
}
