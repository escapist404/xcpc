#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n, k;
            std::cin >> n >> k;
            std::vector<int> a(n);
            for (auto& i : a) std::cin >> i;

            int first = a[k - 1];
            std::sort(a.begin(), a.end());
            a.erase(std::unique(a.begin(), a.end()), a.end());

            int n1 = a.size();
            bool ok = true;
            for (int i = 0; i < n1 - 1; ++i) {
                if (a[i + 1] - a[i] > first) {
                    ok = false;
                }
            }

            if (ok) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }
}