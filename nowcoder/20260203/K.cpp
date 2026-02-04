#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    switch (n) {
        case 1:
            std::cout << "YES\n1\n";
            break;
        case 3:
            std::cout << "YES\n1 2 3\n";
            break;
        default:
            std::cout << "NO\n";
            break;
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
