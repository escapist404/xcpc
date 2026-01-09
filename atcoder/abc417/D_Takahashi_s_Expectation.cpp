#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <tuple>

int main() {
    int N;
    std::cin >> N;

    std::vector<int> P(N), A(N), B(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> P[i] >> A[i] >> B[i];
    }

    std::vector<std::vector<int>> f(N + 1, std::vector<int>(1001));
    for (int i = 0; i <= 1001; ++i) {
        f[N][i] = i;
    }
    for (int i = N - 1; i >= 0; --i) {
        for (int j = 0; j <= P[i]; ++j) {
            f[i][j] = f[i + 1][j + A[i]];
        }
        for (int j = P[i] + 1; j <= 1000; ++j) {
            f[i][j] = f[i + 1][std::max(j - B[i], 0)];
        }
    }

    std::vector<int> PB(N + 1);
    for (int i = 1; i <= N; ++i) {
        PB[i] = PB[i - 1] + B[i - 1];
    }

    int Q;
    std::cin >> Q;
    for (int i = 0; i < Q; ++i) {
        int x;
        std::cin >> x;
        int j = std::lower_bound(PB.begin(), PB.end(), x - 1000) - PB.begin();
        if (j > N) {
            std::cout << x - PB[N] << "\n";
        } else {
            std::cout << f[j][x - PB[j]] << "\n";
        }
    }

    return 0;
}