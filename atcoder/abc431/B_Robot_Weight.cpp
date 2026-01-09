#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int X, N;
    std::cin >> X >> N;

    std::vector<int> W(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> W[i];
    }

    int Q;
    std::cin >> Q;
    std::vector<bool> v(N);
    for (int i = 0; i < Q; ++i) {
        int x;
        std::cin >> x;
        --x;
        if (v[x] == 0) {
            X += W[x];
            v[x] = 1;
        } else {
            X -= W[x];
            v[x] = 0;
        }
        std::cout << X << "\n";
    }

    return 0;
}