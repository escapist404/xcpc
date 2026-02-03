#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

int main() {
    std::string s;
    std::cin >> s;

    std::cout << std::count(s.begin(), s.end(), 'i') + std::count(s.begin(), s.end(), 'j') << "\n";
    return 0;
}
