#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            std::string s;
            std::cin >> s;
            for (int i = 0; i < 10; ++i) {
                if (s.find(i + '0') != std::string::npos) {
                    std::cout << i << "\n";
                    break;
                }
            }
        }();
    }
}