#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    i64 N;
    int M;
    std::cin >> N >> M;

    std::vector<std::pair<i64, i64>> P(M);
    for (int i = 0; i < M; ++i) {
        auto& [A, B] = P[i];
        std::cin >> A >> B;
    }

    std::sort(P.begin(), P.end(), [](auto x, auto y) {
        if (x.first - x.second != y.first - y.second) {
            return x.first - x.second < y.first - y.second;
        }
        return x < y;
    });

    i64 ans = 0;
    for (int i = 0; i < M; ++i) {
        auto [A, B] = P[i];
        ans += std::max(N - B, 0LL) / (A - B);
        N -= std::max(N - B, 0LL) / (A - B) * (A - B);
    }
    
    std::cout << ans << "\n";

    return 0;
}
