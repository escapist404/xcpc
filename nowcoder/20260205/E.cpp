#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using i64 = long long;

int main() {
    int n;
    std::cin >> n;

    if (n == 1) {
        std::cout << "0\n";
        return 0;
    }

    if (n == 2) {
        std::cout << "10\n00\n";
        return 0;
    }

    if (n == 3) {
        std::cout << "111\n100\n101\n";
        return 0;
    }

    std::vector<std::vector<int>> s(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i % 2 == 0 && j % 2 == 0) {
                s[i][j] = 1;
            } else if (i % 2 == 1 && j % 2 == 1) {
                s[i][j] = 0;
            } else if ((i % 2 == 1 && i / 2 > j / 2) || (j % 2 == 1 && j / 2 > i / 2)) {
                s[i][j] = 1;
            } else {
                s[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < ((n + 1) / 2) * 3 - 1 - n; i += 1 + (i % 2 == 0)) {
        // int j =
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << s[i][j];
        }
        std::cout << "\n";
    }

    return 0;
}
