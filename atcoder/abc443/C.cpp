#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    int n, t;
    std::cin >> n >> t;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int last = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] > last) {
            ans += a[i] - last;
            last = a[i] + 100;
        }
    }
    ans += std::max(t - last, 0);

    std::cout << ans << "\n";
    return 0;
}
