#include <iostream>

int main() {
    int d, f;
    std::cin >> d >> f;

    --f;
    while (f < d) {
        f += 7;
    }

    std::cout << (f - d) % 7 + 1 << "\n";

    return 0;
}
