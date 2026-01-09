#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, m;
            std::cin >> n >> m;
            std::cout << "YES\n";
            if (m % 2 == 0) {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        std::cout << i * m + j + 1 << " ";
                    }
                    std::cout << "\n";
                }
            } else {
                for (int i = 0; i < n; ++i) {
                    if (i % 2 == 0) {
                        for (int j = 0; j < m; ++j) {
                            std::cout << i * m + j + 1 << " ";
                        }
                    } else {
                        std::cout << (i + 1) * m << " ";
                        for (int j = 0; j < m - 1; ++j) {
                            std::cout << i * m + j + 1 << " ";
                        }
                    }
                    std::cout << "\n";
                }
            }
        }();
    }
}
