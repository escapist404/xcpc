#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <numeric>

int main() {
    using i64 = long long;
    i64 X, Y;
    std::cin >> X >> Y;

    for (int i = 3; i <= 10; ++i) {
        i64 a = X + Y;
        auto S = std::to_string(a);
        while (S.size() && S.back() == '0') {
            S.pop_back();
        }

        std::reverse(S.begin(), S.end());
        X = Y;
        Y = std::stoll(S);
    }

    std::cout << Y << "\n";
}