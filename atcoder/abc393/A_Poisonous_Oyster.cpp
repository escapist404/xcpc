#include <bits/stdc++.h>

int main() {
    std::string s, t;
    std::cin >> s >> t;

    int a = (s == "fine");
    int b = (t == "fine");

    std::cout << 2 * a + b + 1 << "\n";
}