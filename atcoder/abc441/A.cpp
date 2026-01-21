#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int p, q, x, y;
    std::cin >> p >> q >> x >> y;

    if (x - p < 100 && y - q < 100 && x >= p && y >= q) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}
