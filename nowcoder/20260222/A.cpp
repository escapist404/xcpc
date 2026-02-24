#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int x;
    std::cin >> x;

    std::cout << (x + 5) % 24 << "\n";

    return 0;
}
