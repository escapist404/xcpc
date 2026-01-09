#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int a, b, c;
    std::cin >> a >> b >> c;

    std::cout << "100\n";
    for (int i = 0; i < 50; ++i) {
        std::cout << a << " ";
    }

    for (int i = 50; i < 95; ++i) {
        std::cout << b << " ";
    }

    for (int i = 95; i < 99; ++i) {
        std::cout << c << " ";
    }

    std::cout << c + 1 << "\n";

    return 0;
}
