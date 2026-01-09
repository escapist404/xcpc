#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;
            std::vector<int> a(n), b(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> a[i];
            }
            for (int i = 0; i < n; ++i) {
                std::cin >> b[i];
            }

            int ans = 0;
            for (int i = 0; i < n; ++i) {
                if (a[i] > b[i]) {
                    ans += a[i] - b[i];
                }
            }

            std::cout << ans + 1 << "\n";
        }();
    }
}