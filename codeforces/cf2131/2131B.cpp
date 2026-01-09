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
            std::vector<int> a(n);
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 1) {
                    if (i == n - 1) {
                        std::cout << 2 << " ";
                    } else {
                        std::cout << 3 << " ";
                    }
                } else {
                    std::cout << -1 << " ";
                }
            }
            std::cout << "\n";
        }();
    }
}