#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M, K;
    std::cin >> N >> M >> K;

    std::multiset<int> H, B;
    for (int i = 0; i < N; ++i) {
        int x;
        std::cin >> x;
        H.insert(x);
    }
    for (int i = 0; i < M; ++i) {
        int x;
        std::cin >> x;
        B.insert(x);
    }

    int P = 0;
    for (auto i : H) {
        auto j = B.lower_bound(i);
        if (j != B.end()) {
            B.erase(j);
            ++P;
        }
    }

    if (P >= K) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}