#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> A(N);
            for (auto& i : A) std::cin >> i;

            std::vector<int> prefix_min(N, 1000001), suffix_max(N);
            for (int i = 1; i < N; ++i) {
                prefix_min[i] = std::min(prefix_min[i - 1], A[i - 1]);
            }
            for (int i = N - 2; i >= 0; --i) {
                suffix_max[i] = std::max(suffix_max[i + 1], A[i + 1]);
            }

            for (int i = 0; i < N; ++i) {
                if (prefix_min[i] >= A[i] || suffix_max[i] <= A[i]) {
                    std::cout << "1";
                } else {
                    std::cout << "0";
                }
            }

            std::cout << "\n";
        }();
    }
}