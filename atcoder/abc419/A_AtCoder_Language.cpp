#include <bits/stdc++.h>

int main() {
    std::string S;
    std::cin >> S;
    if (S == "red") {
        std::cout << "SSS\n";
    } else if (S == "blue") {
        std::cout << "FFF\n";
    } else if (S == "green") {
        std::cout << "MMM\n";
    } else {
        std::cout << "Unknown\n";
    }
}