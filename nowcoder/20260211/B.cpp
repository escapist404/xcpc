#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << "/\\"[(i & 1) ^ (j & 1)];
        }
        std::cout << "\n";
    }

    return 0;
}
