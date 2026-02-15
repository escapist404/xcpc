#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void solve() {
    int n, w;
    std::cin >> n >> w;
    std::cout << n / w * (w - 1) + n % w << "\n";
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
