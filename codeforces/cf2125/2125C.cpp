#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            using i64 = long long;
            auto count = [](i64 x) {
                i64 answer = x;
                answer -= x / 2;
                answer -= x / 3;
                answer -= x / 5;
                answer -= x / 7;
                answer += x / 6;
                answer += x / 15;
                answer += x / 35;
                answer += x / 10;
                answer += x / 21;
                answer += x / 14;
                answer -= x / 30;
                answer -= x / 42;
                answer -= x / 70;
                answer -= x / 105;
                answer += x / 210;
                return answer;
            };

            i64 l, r;
            std::cin >> l >> r;
            std::cout << count(r) - count(l - 1) << "\n";
        }();
    }
}