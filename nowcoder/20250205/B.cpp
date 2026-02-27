#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int maxv = *std::max_element(a.begin(), a.end());
    int maxc = std::count(a.begin(), a.end(), maxv);

    for (int i = 0; i < n; ++i) {
        std::cout << (maxc - (a[i] == maxv) + 1) % 2;
    }
    std::cout << "\n";
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
