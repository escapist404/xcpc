#include <bits/stdc++.h>

int main() {
    std::string s;
    std::cin >> s;

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (std::count(s.begin(), s.end(), ch) == 1) {
            std::cout << ch << "\n";
            return 0;
        }
    }
}