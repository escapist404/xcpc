#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

int main() {
    int n;
    std::cin >> n;

    if (n % 10 == 0) {
        std::cout << 1 << "\n";
    } else if (n % 5 == 0) {
        std::cout << 2 << "\n";
    } else if (n % 2 == 0) {
        std::cout << 5 << "\n";
    } else {
        std::cout << 10 << "\n";
    }

    return 0;
}
