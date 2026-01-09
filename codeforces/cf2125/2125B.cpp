#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            using i64 = long long;
            i64 a, b, k;
            std::cin >> a >> b >> k;
            if (k >= std::max(a, b) / std::gcd(a, b)) {
                std::cout << 1 << "\n";
            } else {
                std::cout << 2 << "\n";
            }
        }();
    }
}