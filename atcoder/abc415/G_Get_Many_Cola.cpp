#include <bits/stdc++.h>

using i64 = long long;
const int V = 300;
const int V2 = V * V;

int main() {
    i64 N;
    int M;
    std::cin >> N >> M;

    std::vector<int> Z(V + 1, -1);
    for (int i = 0; i < M; ++i) {
        int A, B;
        std::cin >> A >> B;

        Z[A] = std::max(Z[A], B);
    }

    std::vector<i64> f(V2 + 1);
    std::iota(f.begin(), f.end(), 0);
    for (int i = 0; i <= V; ++i) {
        if (Z[i] == -1) {
            continue;
        }
        for (int j = i; j <= V2; ++j) {
            f[j] = std::max(f[j - i + Z[i]] + i, f[j]);
        }
    }

    if (N <= V2) {
        std::cout << f[N] << "\n";
    } else {
        int idx = -1;
        for (int i = 0; i <= V; ++i) {
            if (Z[i] == -1) {
                continue;
            }
            if (idx == -1 || 1LL * Z[idx] * (i - Z[i]) < 1LL * Z[i] * (idx - Z[idx])) {
                idx = i;
            }
        }
        i64 ans = 0;
        for (int i = idx; i <= V2; ++i) {
            ans = std::max(f[i] + (N - i) / (idx - Z[idx]) * idx, ans);
        }
        std::cout << ans << "\n";
    }

    return 0;
}
