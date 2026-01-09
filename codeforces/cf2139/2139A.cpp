#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int a, b;
            std::cin >> a >> b;
            if (a < b) std::swap(a, b);
            if (a == b) {
                std::cout << 0 << "\n";
            } else if (a % b == 0) {
                std::cout << 1 << "\n";
            } else {
                std::cout << 2 << "\n";
            }
        }();
    }

    return 0;
}