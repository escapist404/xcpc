#include <iostream>

int main() {
    std::cout << "1\n2000000 2000000\n";
    for (int i = 1; i <= 2000000; ++i) {
        std::cout << i << " " << i << " " << i << "\n";
    }
}