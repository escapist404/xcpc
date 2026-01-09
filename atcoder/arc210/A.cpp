#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<i64> d(N + 1), m(N, 1);
    for (int i = 0; i < Q; ++i) {
        int idx, add;
        std::cin >> idx >> add;

        --idx;
        d[idx] += add;
        m[idx] = std::max(m[idx], d[idx] - d[idx + 1] + 1);
    }

    i64 ans = 0, sum = 1;
    for (int i = 0; i < N; ++i) {
        ans += sum;
        sum += m[i];
    }

    std::cout << ans << "\n";
    return 0;
}
