#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using i64 = long long;

void solve() {
    i64 n;
    std::cin >> n;

    i64 a = n;
    while ((a ^ n) != a + n) {
        a <<= 1;
    }

    std::cout << a + n << " " << a << "\n";
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
