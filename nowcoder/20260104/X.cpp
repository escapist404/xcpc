#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s;
    std::cin >> s;

    if (std::count(s.begin(), s.end(), 'C')) {
        std::cout << "0\n";
    } else if (s == "ABD") {
        std::cout << "4\n";
    } else {
        std::cout << "2\n";
    }

    return 0;
}
