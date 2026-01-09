#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

int main() {
    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }

    std::sort(A.begin(), A.end());

    using i64 = long long;
    std::vector<i64> P(N + 1);
    for (int i = 1; i <= N; ++i) {
        P[i] = P[i - 1] + A[i - 1];
    }

    for (int i = 0; i < Q; ++i) {
        int B;
        std::cin >> B;

        if (B > A.back()) {
            std::cout << -1 << "\n";
            continue;
        }

        int id = std::lower_bound(A.begin(), A.end(), B) - A.begin();
        std::cout << P[id] + 1LL * (N - id) * (B - 1) + 1 << "\n";
    }

    return 0;
}