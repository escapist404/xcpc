#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<int> W(N), H(N), B(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> W[i] >> H[i] >> B[i];
    }

    int V = std::accumulate(W.begin(), W.end(), 0);
    std::vector<i64> f(V + 1, -1E14);
    f[0] = 0;
    for (int i = 0; i < N; ++i) {
        auto g = std::vector<i64>(V + 1);
        for (int j = 0; j < W[i]; ++j) {
            g[j] = f[j] + B[i];
        }
        for (int j = W[i]; j <= V; ++j) {
            g[j] = std::max(f[j] + B[i], f[j - W[i]] + H[i]);
        }
        f = g;
    }

    std::cout << *std::max_element(f.begin(), f.begin() + V / 2 + 1) << "\n";

    return 0;
}