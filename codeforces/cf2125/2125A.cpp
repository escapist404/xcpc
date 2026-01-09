#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        std::string s;
        std::cin >> s;
        std::sort(s.begin(), s.end());
        std::reverse(s.begin(), s.end());
        std::cout << s << "\n";
    }
}