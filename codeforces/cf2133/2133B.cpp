#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

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

            std::sort(A.begin(), A.end(), std::greater<int>());
            using i64 = long long;
            i64 answer = 0;
            int min = 1e9;
            for (int i = 0; i < N; i += 2) {
                answer += A[i];
            }

            std::cout << answer << "\n";
        }();
    }
}