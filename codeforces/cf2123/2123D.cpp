#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, K;
            std::cin >> N >> K;
            std::string S;
            std::cin >> S;
            if (std::count(S.begin(), S.end(), '1') <= K || 2 * K > N) {
                std::cout << "Alice\n";
            } else {
                std::cout << "Bob\n";
            }
        }();
    }
}