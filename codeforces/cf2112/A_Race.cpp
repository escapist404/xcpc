#include <iostream>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int a, x, y;
            std::cin >> a >> x >> y;
            if (x > y) std::swap(x, y);
            if (a < x  || a > y) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }
}