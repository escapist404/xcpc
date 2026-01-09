#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    std::string s, t;
    std::cin >> s >> t;

    bool ok = true;
    for (int i = 0; i < n; ++i) {
        if ((s[i] == '1' || t[i] == '1') == false) {
            ok = false;
        }
    }

    std::cout << ok << "\n";
    return 0;
}