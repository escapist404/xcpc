#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int H, W;
    std::cin >> H >> W;

    std::vector<std::vector<int>> A(H, std::vector<int>(W));
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            std::cin >> A[i][j];
        }
    }

    std::vector<int> P(H + W - 1);
    for (int i = 0; i < H + W - 1; ++i) {
        std::cin >> P[i];
    }

    std::vector<std::vector<i64>> f(H + 1, std::vector<i64>(W + 1, 1E18));
    f[H - 1][W] = f[H][W - 1] = 0;
    for (int i = H - 1; i >= 0; --i) {
        for (int j = W - 1; j >= 0; --j) {
            f[i][j] = std::max(std::min(f[i + 1][j], f[i][j + 1]) + P[i + j] - A[i][j], 0LL);
        }
    }

    std::cout << f[0][0] << "\n";

    return 0;
}
