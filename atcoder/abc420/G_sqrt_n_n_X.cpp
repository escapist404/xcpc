#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    using i64 = long long;
    using i128 = __int128_t;
    i64 X;
    std::cin >> X;

    /*
    
        4n^2 + 4n + 4X = (2P)^2 \implies (2P)^2 - (2n + 1)^2 = 4X - 1
        \implies (2P + 2n + 1) * (2P - 2n - 1) = 4X - 1

        Iterate all divisors of (4X - 1), denoting u and v (u > v), i.e. uv = 4X - 1.
        Then we have P = (u + v) / 4, n = (u - v - 2) / 4
        Considering the constraints for integers, { u mod 4, v mod 4 } = { 1, 3 }
    
    */

    i64 Y = 4 * X - 1;
    std::vector<i64> answer;
    for (i64 v = -20000001LL; v <= 20000001LL; ++v) {
        if (v != 0 && Y % v == 0) {
            i64 u = Y / v;
            i64 P = (u + v) / 4;
            i64 n = (u - v - 2) / 4;
            if ((i128)n * n + n + X == (i128)P * P) {
                answer.push_back(n);
            }
        }
    }

    std::sort(answer.begin(), answer.end());
    answer.erase(std::unique(answer.begin(), answer.end()), answer.end());

    std::cout << answer.size() << "\n";
    for (int i = 0; i < (int)answer.size(); ++i) {
        std::cout << answer[i] << " \n"[i + 1 == (int)answer.size()];
    }

    return 0;
}
