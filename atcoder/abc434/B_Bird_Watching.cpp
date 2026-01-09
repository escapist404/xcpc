#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> s(M), c(M);
    for (int i = 0; i < N; ++i) {
        int A, B;
        std::cin >> A >> B;
        --A;
        s[A] += B;
        c[A]++;
    }

    for (int i = 0; i < M; ++i) {
        std::cout << std::fixed << std::setprecision(15) << s[i] / c[i] << "\n";
    }

    return 0;
}
