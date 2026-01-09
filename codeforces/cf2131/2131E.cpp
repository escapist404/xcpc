#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> a(N), b(N);
            for (int i = 0; i < N; ++i) {
                std::cin >> a[i];
            }
            for (int i = 0; i < N; ++i) {
                std::cin >> b[i];
            }

            if (a.back() != b.back()) {
                std::cout << "NO\n";
                return;
            }

            for (int i = N - 2; i >= 0; --i) {
                if (a[i] != b[i]) {
                    if (((a[i] ^ b[i + 1]) != b[i]) && ((a[i] ^ a[i + 1]) != b[i])) {
                        std::cout << "NO\n";
                        return;
                    }
                }
            }

            std::cout << "YES\n";
        }();
    }
}