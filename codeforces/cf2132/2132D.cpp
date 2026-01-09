#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            using i64 = long long;

            i64 K;
            std::cin >> K;
            std::vector<i64> length(17), sum(17), pow10(17, 1);
            for (i64 i = 1, b = 1; i <= 16; ++i) {
                length[i] = 9LL * i * b;
                sum[i] = 45 * b + 10 * sum[i - 1];
                b *= 10;
                pow10[i] = b;
            }
            i64 end = 0;
            for (int i = 1; i <= 16; ++i) {
                i64 d = std::min(length[i], K);
                end += d / i;
                K -= d / i * i;
            }

            i64 answer = 0;
            std::string D = std::to_string(end + 1);
            for (int i = 0; i < K; ++i) {
                answer += D[i] - '0';
            }
            // std::cerr << end << "\n";

            D = std::to_string(end);
            for (int i = 0; i < (int)D.size(); ++i) {
                i64 d = D[i] - '0';
                answer += d * (d - 1) / 2 * pow10[(int)D.size() - 1 - i];
                answer += sum[(int)D.size() - 1 - i] * d;
                end %= pow10[(int)D.size() - 1 - i];
                answer += d * (end + 1);
            }

            std::cout << answer << "\n";
        }();
    }
}