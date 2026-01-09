#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> pass(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> pass[i];
    }

    if (std::count(pass.begin(), pass.end(), 0) == n) {
        std::cout << 0 << "\n";
        return 0;
    }

    int l = 0;
    while (l < n && pass[l] == 0) {
        ++l;
    }

    int r = n;
    while (r > 0 && pass[r - 1] == 0) {
        --r;
    }

    std::cout << r - l - 1 << "\n";
    return 0;
}
