#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N, K;
            std::cin >> N >> K;
            std::vector<int> A(N);
            for (int i = 0; i < N; ++i) {
                std::cin >> A[i];
            }

            for (int i = 0; i < N; ++i) {
                int res = A[i] % (K + 1);
                if (res == 0) {
                    std::cout << A[i] << " \n"[i + 1 == N];
                } else {
                    std::cout << A[i] + 1LL * res * K << " \n"[i + 1 == N];
                }
            }
        }();
    }

    return 0;
}
