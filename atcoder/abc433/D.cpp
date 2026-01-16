#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>

using i64 = long long;
const int D = 10;

const i64 power10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000LL};

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    auto digit = [](int x) {
        int c = 0;
        do {
            x /= 10;
            c++;
        } while (x);
        return c;
    };

    std::vector<std::unordered_map<int, int>> freq(D + 1);
    for (int i = 0; i < n; ++i) {
        freq[digit(a[i])][a[i] % m]++;
    }

    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        int g = a[i] % m;
        for (int d = 1; d <= D; ++d) {
            int r = (-1LL * g * (power10[d] % m) % m + m) % m;
            ans += freq[d][r];
        }
    }

    std::cout << ans << "\n";

    return 0;
}
