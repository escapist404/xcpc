#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    std::string s;
    std::cin >> s;
    s.erase((int)s.size() / 2, 1);
    std::cout << s << "\n";
    return 0;
}
