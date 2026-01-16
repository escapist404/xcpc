#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int x, y, z;
    std::cin >> x >> y >> z;
    if (x - z * y >= 0 && (x - z * y) % (z - 1) == 0) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}
