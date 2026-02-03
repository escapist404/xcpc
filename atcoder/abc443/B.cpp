#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    int n, k;
    std::cin >> n >> k;

    int l = -1, r = 1E9;
    while (l + 1 < r) {
        int m = l + (r - l) / 2;
        if (1LL * (2 * n + m) * (m + 1) / 2 >= k) {
            r = m;
        } else {
            l = m;
        }
    }

    std::cout << r << "\n";
    return 0;
}
