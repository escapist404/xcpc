#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

void solve() {
    int a, b, c;
    std::cin >> a >> b >> c;

    int max = std::max({a, b, c});
    int min = std::min({a, b, c});
    if (max - min >= 2) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
    }
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
