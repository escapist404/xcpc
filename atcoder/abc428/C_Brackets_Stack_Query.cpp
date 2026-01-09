#include <bits/stdc++.h>

int main() {
    int q;
    std::cin >> q;

    std::string s;
    int c = 0, d = 0;

    std::vector<std::pair<int, int>> stack = {{0, 0}};

    while (q--) {
        int type;
        std::cin >> type;

        if (type == 1) {
            char ch;
            std::cin >> ch;
            
            if (ch == '(') {
                c++;
            } else {
                if (c) {
                    c--;
                } else {
                    d++;
                }
            }
            stack.push_back({c, d});
        } else {
            stack.pop_back();
            c = stack.back().first;
            d = stack.back().second;
        }

        if (c == 0 && d == 0) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }

    return 0;
}