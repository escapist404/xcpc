#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << (a[i] + (i == j)) % 998244353 << " \n"[j == n - 1];
        }
    }

    return 0;
}
