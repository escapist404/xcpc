#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;
            int last = -1;
            bool ans = true;
            for (int i = 0; i < n; ++i) {
                int x;
                std::cin >> x;
                if (x != -1) {
                    if (last == -1) {
                        last = x;
                    }
                    if (x != last) {
                        ans = false;
                    }
                }
            }

            if (ans && last != 0) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }();
    }

    return 0;
}
