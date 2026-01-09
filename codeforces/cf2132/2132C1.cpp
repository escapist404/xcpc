#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            long long N, K;
            // std::cin >> N >> K;
            std::cin >> N;

            std::vector<long long> pow3(20, 1);
            for (int i = 1; i < 20; ++i) {
                pow3[i] = pow3[i - 1] * 3;
            }

            std::vector<long long> count(20);
            for (int i = 19; i >= 0; --i) {
                while (N >= pow3[i]) {
                    N -= pow3[i];
                    count[i]++;
                    // --K;
                }
            }

            // for (int i = 19; i >= 1; --i) {
            //     long long d = std::max(std::min(K / 2, (long long)count[i]), 0LL);
            //     count[i] -= d;
            //     count[i - 1] += 3 * d;
            //     K -= 2 * d;
            // }

            // if (K < 0) {
            //     std::cout << -1 << "\n";
            //     return;
            // }

            long long answer = 3LL * count[0];
            for (int i = 1; i < 20; ++i) {
                answer += 1LL * count[i] * (3LL * pow3[i] + i * pow3[i - 1]);
            }

            std::cout << answer << "\n";
        }();
    }
}