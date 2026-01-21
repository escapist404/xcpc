#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

int main() {
    int n, k;
    i64 x;
    std::cin >> n >> k >> x;

    std::vector<int> a(n);
    for (auto& i : a) {
        std::cin >> i;
    }

    std::sort(a.begin(), a.end());
    i64 s = std::accumulate(a.begin(), a.begin() + k, 0LL);

    if (s < x) {
        std::cout << "-1\n";
        return 0;
    }

    i64 r = 0;
    for (int i = 0; i < n; ++i) {
        if (r + a[i] > s - x) {
            std::cout << n - i << "\n";
            return 0;
        }
        r += a[i];
    }

    return 0;
}
