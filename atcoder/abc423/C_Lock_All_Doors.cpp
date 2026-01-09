#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, r;
    std::cin >> n >> r;

    std::vector<int> locked(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> locked[i];
    }

    if (std::count(locked.begin(), locked.end(), 1) == n) {
        std::cout << 0 << "\n";
        return 0;
    }

    int fir = std::find(locked.begin(), locked.end(), 0) - locked.begin();
    int lst = n - (std::find(locked.rbegin(), locked.rend(), 0) - locked.rbegin());
    fir = std::min(fir, r);
    lst = std::max(lst, r);

    std::cout << lst - fir + std::count(locked.begin() + fir, locked.begin() + lst, 1) << "\n";

    return 0;
}
