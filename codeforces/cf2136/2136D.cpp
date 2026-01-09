#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    using i64 = long long;
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            auto move = [&](char type, i64 k) {
                std::cout << "? " << type << " " << k << std::endl;
                i64 result;
                std::cin >> result;
                return result;
            };

            int N;
            std::cin >> N;
            i64 min1 = 4000000000LL, min2 = 4000000000LL;
            for (int i = 0; i < N; ++i) {
                i64 x, y;
                std::cin >> x >> y;
                min1 = std::min(min1, x + y + 2000000000LL);
                min2 = std::min(min2, y - x + 2000000000LL);
            }

            move('L', 1000000000);
            move('L', 1000000000);
            move('D', 1000000000);
            move('D', 1000000000);
            i64 v1 = move('R', 0) - min1;
            move('R', 1000000000);
            move('R', 1000000000);
            move('R', 1000000000);
            move('R', 1000000000);
            i64 v2 = move('R', 0) - min2;

            i64 Y = 1000000000LL - (v1 + v2 - 2000000000LL) / 2;
            i64 X = 1000000000LL - (v1 - v2 + 2000000000LL) / 2;

            std::cout << "! " << X << " " << Y << std::endl;
        }();
    }
}