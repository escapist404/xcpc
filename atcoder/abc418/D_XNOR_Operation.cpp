#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <array>

int main() {
    int N;
    std::cin >> N;
    std::string T;
    std::cin >> T;

    std::vector<std::array<int, 2>> f(N + 1);
    for (int i = N - 1; i >= 0; --i) {
        if (T[i] == '0') {
            f[i][0] = f[i + 1][1] + 1;
            f[i][1] = f[i + 1][0];
        } else {
            f[i][0] = f[i + 1][0];
            f[i][1] = f[i + 1][1] + 1;
        }
    }

    using i64 = long long;
    i64 answer = 0;
    for (int i = 0; i < N; ++i) {
        answer += f[i][1];
    }

    std::cout << answer << "\n";

    return 0;
}