#include <bits/stdc++.h>

int main() {
    std::string s, t;
    std::cin >> s >> t;

    int a, b;
    if (s[0] == 'O') {
        a = 0;
    } else if (s[0] == 'S') {
        a = 1;
    } else {
        a = 2;
    }
    if (t[0] == 'O') {
        b = 0;
    } else if (t[0] == 'S') {
        b = 1;
    } else {
        b = 2;
    }

    if (a >= b) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}