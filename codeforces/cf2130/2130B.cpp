#include <vector>
#include <iostream>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, S;
            std::cin >> N >> S;
            std::vector<int> C(3);
            for (int i = 0; i < N; ++i) {
                int v;
                std::cin >> v;
                C[v]++;
            }

            int sum = C[1] + 2 * C[2];
            if (sum > S) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < C[i]; ++j) {
                        std::cout << i << " ";
                    }
                }
                std::cout << "\n";
                return;
            }
            if (sum + 1 == S) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < C[i * 2 % 3]; ++j) {
                        std::cout << i * 2 % 3 << " ";
                    }
                }
                std::cout << "\n";
                return;
            }
            std::cout << -1 << "\n";
        }();
    }
}
