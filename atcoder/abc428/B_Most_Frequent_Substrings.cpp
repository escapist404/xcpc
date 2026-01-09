#include <bits/stdc++.h>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::string s;
    std::cin >> s;

    std::vector<std::set<std::string>> occ(n + 1);
    for (int i = 0; i <= n - k; ++i) {
        std::string t = s.substr(i, k);
        int c = 0;
        for (int j = 0; j <= n - k; ++j) {
            if (s.substr(j, k) == t) {
                ++c;
            }
        }
        occ[c].insert(t);
    }

    for (int i = n; i >= 1; --i) {
        if (occ[i].size() >= 1) {
            std::cout << i << "\n";
            for (auto j : occ[i]) {
                std::cout << j << " ";
            }
            std::cout << "\n";
            break;
        }
    }

    return 0;
}