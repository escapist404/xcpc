#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            using i64 = long long;
            i64 X;
            std::cin >> X;
            i64 b = 1;
            std::vector<i64> answer;
            for (int i = 1; i <= 17; ++i) {
                b *= 10;
                if (X % (b + 1) == 0) {
                    answer.push_back(X / (b + 1));
                }
            }
            std::reverse(answer.begin(), answer.end());
            std::cout << answer.size() << "\n";
            for (auto i : answer) {
                std::cout << i << " ";
            }
            if (answer.size()) std::cout << "\n";
        }();
    }
}