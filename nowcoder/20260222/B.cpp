#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void solve() {
    std::string s;
    std::cin >> s;

    if (s.find('5') != std::string::npos || s.find('0') != std::string::npos) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
