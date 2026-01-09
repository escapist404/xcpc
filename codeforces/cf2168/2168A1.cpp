#include <bits/stdc++.h>

void first() {
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        for (int j = 0; j < 7; ++j) {
            int k = x % 26;
            x /= 26;
            std::cout << (char)('a' + k);
        }
    }

    std::cout << "\n";
}

void second() {
    std::string s;
    std::cin >> s;

    std::cout << s.size() / 7 << "\n";
    for (int i = 0; i < (int)s.size(); i += 7) {
        int v = 0;
        for (int j = 6; j >= 0; --j) {
            v *= 26;
            v += s[i + j] - 'a';
        }
        std::cout << v << " ";
    }
    std::cout << "\n";
}

int main() {
    std::string flag;
    std::cin >> flag;

    if (flag == "first") {
        first();
    } else {
        second();
    }

    return 0;
}
