#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

const int P = 998244353;

int main() {
    int s;
    std::cin >> s;

    int ans = 0;
    for (int i = 2; i <= s - 4; ++i) {
        for (int j = 2; i + j <= s - 2; ++j) {
            int k = s - i - j;
            (ans += 1LL * (s - std::max({i, j, k})) * (i - 1) * (j - 1) * (k - 1) % P) %= P;
        }
    }

    std::cout << ans << "\n";
}
