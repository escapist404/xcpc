#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <list>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;
            
            std::vector<int> B(n);
            for (auto& i : B) {
                std::cin >> i;
            }

            int min = B[0];
            bool ok = true;
            for (int i = 1; i < n; ++i) {
                if (min * 2 <= B[i]) ok = false;
                min = std::min(min, B[i]);
            }

            if (ok) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }
}
