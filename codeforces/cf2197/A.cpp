#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    int a = 0;
    for (int d = 0; d <= 81; ++d) {
        int x = n + d;
        int c = 0;
        while (x) {
            c += x % 10;
            x /= 10;
        }
        if (c == d) {
            ++a;
        }
    }

    std::cout << a << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}