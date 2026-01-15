#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    int n;
    std::string s;
    std::cin >> n >> s;
    for (int i = 0; i < n - (int)s.size(); ++i) {
        std::cout << "o";
    }
    std::cout << s << "\n";

    return 0;
}
