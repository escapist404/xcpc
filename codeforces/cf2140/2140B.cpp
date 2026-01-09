#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;
            std::cout << 2 * n << "\n";
        }();
    }
}
