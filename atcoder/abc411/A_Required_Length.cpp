#include <cstring>
#include <iostream>

int main() {
    std::string S;
    int L;
    std::cin >> S >> L;
    if (S.size() >= L) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    return 0;
}