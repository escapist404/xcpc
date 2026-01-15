#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    if (s.find("2025") != std::string::npos && s.find("2026") == std::string::npos) {
        std::cout << "1\n";
    } else {
        std::cout << "0\n";
    }
}

int main() {
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
