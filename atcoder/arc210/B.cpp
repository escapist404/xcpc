#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int N, M, Q;
    std::cin >> N >> M >> Q;

    std::vector<int> A(N), B(M);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }
    for (int i = 0; i < M; ++i) {
        std::cin >> B[i];
    }

    return 0;
}
