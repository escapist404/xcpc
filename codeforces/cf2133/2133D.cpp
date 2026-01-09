#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> H(N);
            for (int i = 0; i < N; ++i) {
                std::cin >> H[i];
            }

            using i64 = long long;
            std::vector<i64> f(N + 1, 1e18);
            f[N] = 0;
        }();
    }
}