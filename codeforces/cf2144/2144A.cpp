#include <bits/stdc++.h>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;

            std::vector<int> a(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> a[i];
            }

            int sum = std::accumulate(a.begin(), a.end(), 0) % 3;

            if (sum != 0) {
                std::cout << 0 << " " << 0 << "\n";
                return;
            }

            std::cout << 1 << " " << 2 << "\n";
        }();
    }
}
