#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

void solve() {
    int a, b;
    std::cin >> a >> b;

    if (a >= b) {
        int x = a / (b + 1);
        int y = a % (b + 1);
        int r = b;
        for (int i = 0; i < y; ++i) {
            for (int j = 0; j < x + 1; ++j) {
                std::cout << "0";
            }
            if (r) {
                --r;
                std::cout << "1";
            }
        }
        for (int i = y; i < b + 1; ++i) {
            for (int j = 0; j < x; ++j) {
                std::cout << "0";
            }
            if (r) {
                --r;
                std::cout << "1";
            }
        }
        std::cout << "\n";
    } else {
        int x = b / (a + 1);
        int y = b % (a + 1);
        int r = a;
        for (int i = 0; i < y; ++i) {
            for (int j = 0; j < x + 1; ++j) {
                std::cout << "1";
            }
            if (r) {
                --r;
                std::cout << "0";
            }
        }
        for (int i = y; i < a + 1; ++i) {
            for (int j = 0; j < x; ++j) {
                std::cout << "1";
            }
            if (r) {
                --r;
                std::cout << "0";
            }
        }
        std::cout << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
