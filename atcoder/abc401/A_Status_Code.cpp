#include <vector>
#include <iostream>

int main() {
    int S;
    std::cin >> S;
    if (S >= 200 && S <= 299) {
        std::cout << "Success\n";
    } else {
        std::cout << "Failure\n";
    }
}