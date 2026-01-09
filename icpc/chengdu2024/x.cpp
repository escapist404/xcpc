#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;

    if (b == 0) {
        std::cout << (a == 0) << "\n";
    } else {
        std::cout << (a % b == 0) << "\n";
    }

    return 0;
}