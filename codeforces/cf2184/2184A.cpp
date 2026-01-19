#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

void solve() {
    int n;
    std::cin >> n;
    if (n <= 3) {
        std::cout << n << "\n";
    } else if (n % 2 == 0) {
        std::cout << 0 << "\n";
    } else {
        std::cout << 1 << "\n";
    }
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
