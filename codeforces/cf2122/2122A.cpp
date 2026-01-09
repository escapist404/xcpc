#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, m;
            std::cin >> n >> m;
            if (std::max(n, m) >= 3 && std::min(n, m) >= 2) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }
    return 0;
}
