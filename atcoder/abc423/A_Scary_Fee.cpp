#include <bits/stdc++.h>

int main() {
    int x, c;
    std::cin >> x >> c;

    int b = 0;
    while ((b + 1000) + (b + 1000) / 1000 * c <= x) {
        b += 1000;
    }

    std::cout << b << "\n";
    return 0;
}