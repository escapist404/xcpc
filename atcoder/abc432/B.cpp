#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string X;
    std::cin >> X;

    std::sort(X.begin(), X.end());
    for (int i = 0; i < (int)X.size(); ++i) {
        if (X[i] != '0') {
            std::swap(X[0], X[i]);
            break;
        }
    }

    std::cout << X << "\n";
    return 0;
}
