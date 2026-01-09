#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int N, Q;
    std::cin >> N >> Q;

    std::vector<int> A(N), B(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }
    for (int i = 0; i < N; ++i) {
        std::cin >> B[i];
    }

    using i64 = long long;
    i64 answer = 0;
    for (int i = 0; i < N; ++i) {
        answer += std::min(A[i], B[i]);
    }

    for (int i = 0; i < Q; ++i) {
        char type;
        int X, V;
        std::cin >> type >> X >> V;
        --X;

        answer -= std::min(A[X], B[X]);
        if (type == 'A') {
            A[X] = V;
        } else {
            B[X] = V;
        }
        answer += std::min(A[X], B[X]);

        std::cout << answer << "\n";
    }
    return 0;
}
