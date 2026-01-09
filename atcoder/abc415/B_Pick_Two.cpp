#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string S;
    std::cin >> S;

    std::vector<int> idx;
    for (int i = 0; i < (int)S.size(); ++i) {
        if (S[i] == '#') {
            idx.push_back(i + 1);
        }
    }

    for (int i = 0; i < (int)idx.size(); i += 2) {
        std::cout << idx[i] << "," << idx[i + 1] << "\n";
    }

    return 0;
}
