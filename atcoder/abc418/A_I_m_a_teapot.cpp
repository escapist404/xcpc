#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int N;
    std::cin >> N;
    std::string S;
    std::cin >> S;

    if (S.size() >= 3 && S.substr(S.size() - 3) == "tea") {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}