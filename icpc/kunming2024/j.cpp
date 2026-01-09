#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::string s;
            std::cin >> n >> s;

            std::vector<int> p(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> p[i];
                --p[i];
            }

            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                if (p[i] != i) {
                    ++cnt;
                }
            }

            if (n == 2) {
                std::cout << "Alice\n";
                return;
            }

            if (s == "Bob") {
                std::cout << "Bob\n";
                return;
            }

            if (cnt == 2) {
                std::cout << "Alice\n";
            } else {
                std::cout << "Bob\n";
            }
        }();
    }
}
