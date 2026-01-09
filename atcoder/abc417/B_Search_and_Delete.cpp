#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<int> A(N), B(M);
    for (auto& i : A) std::cin >> i;
    for (auto& i : B) std::cin >> i;

    for (int i = 0; i < M; ++i) {
        auto it = std::lower_bound(A.begin(), A.end(), B[i]);
        if (it != A.end() && *it == B[i]) {
            A.erase(it);
        }
    }

    N = A.size();
    for (int i = 0; i < N; ++i) {
        std::cout << A[i] << " \n"[i == N - 1];
    }

    return 0;
}