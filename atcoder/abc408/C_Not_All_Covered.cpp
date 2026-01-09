#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<int> c(N + 1);
    for (int i = 0; i < M; ++i) {
        int l, r;
        std::cin >> l >> r;
        --l;
        c[l]++;
        c[r]--;
    }

    for (int i = 1; i <= N; ++i) {
        c[i] += c[i - 1];
    }

    std::cout << *std::min_element(c.begin(), c.end() - 1) << "\n";

    return 0;
}
