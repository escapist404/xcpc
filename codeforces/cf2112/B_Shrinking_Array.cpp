#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> A(N);
            for (auto& i : A) std::cin >> i;

            for (int i = 0; i < N - 1; ++i) {
                if (A[i] == A[i + 1] || A[i] == A[i + 1] - 1 || A[i] == A[i + 1] + 1) {
                    std::cout << "0\n";
                    return;
                }
            }

            for (int i = 1; i < N - 1; ++i) {
                if (A[i - 1] > A[i] && A[i] < A[i + 1]) {
                    std::cout << "1\n";
                    return;
                }
                if (A[i - 1] < A[i] && A[i] > A[i + 1]) {
                    std::cout << "1\n";
                    return;
                }
            }

            std::cout << "-1\n";
        }();
    }
}