#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int N;
            std::cin >> N;
            std::vector<int> A(N);

            for (int i = 0; i < N; ++i) {
                std::cin >> A[i];
            }
            
            using i64 = long long;
            i64 answer = 0;

            for (int i = 2; i < N; i += 2) {
                int d = std::max(A[i] + A[i - 2] - A[i - 1], 0);
                A[i] -= d;
                A[i - 2] += std::min(A[i], 0);
                A[i] = std::max(A[i], 0);
                answer += d;
            }

            if (N % 2 == 0) {
                answer += std::max(A[N - 2] - A[N - 1], 0);
            }

            std::cout << answer << "\n";
        }();
    }

    return 0;
}
