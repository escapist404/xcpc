#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    std::string s, t;
    std::cin >> s;

    int ans = 0;
    for (char c : s) {
        if (t.size() % 2 == 0) {
            if (c != 'i') {
                ++ans;
                t.push_back('i');
            }
        } else {
            if (c != 'o') {
                ++ans;
                t.push_back('o');
            }
        }
        t.push_back(c);
    }

    if (t.size() % 2 == 1) {
        ++ans;
    }

    std::cout << ans << "\n";
}