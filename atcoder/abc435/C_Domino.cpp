#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int p = 1;
    for (int i = 0; i < p && i < n; ++i) {
        p = std::max(p, i + a[i]);
    }

    std::cout << std::min(p, n) << "\n";
    return 0;
}
