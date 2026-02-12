#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using i64 = long long;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> mat(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> mat[i][j];
        }
    }

    i64 s = 0;
    for (int i = 0; i < n; ++i) {
        s += std::accumulate(mat[i].begin(), mat[i].end(), 0LL);
    }

    if (s % (n * n) != 0) {
        std::cout << "No\n";
        return 0;
    }

    i64 v = s / (n * n);
    i64 c = v * n;

    for (int i = 0; i < n; ++i) {
        if (std::accumulate(mat[i].begin(), mat[i].end(), 0LL) % 2 != c % 2) {
            std::cout << "No\n";
            return 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        i64 b = 0;
        for (int j = 0; j < n; ++j) {
            b += mat[j][i];
        }
        if (b % 2 != c % 2) {
            std::cout << "No\n";
            return 0;
        }
    }

    if (n == 1) {
        std::cout << "Yes\n";
        return 0;
    }

    // 2n^2 - 2n
    // 2n - 2 + n^2

    for (int i = 0; i < n - 1; ++i) {
        i64 b = std::accumulate(mat[i].begin(), mat[i].end(), 0LL);
        mat[i][0] -= (b - c) / 2;
        mat[i][1] -= (b - c) / 2;
        mat[i + 1][0] += (b - c) / 2;
        mat[i + 1][1] += (b - c) / 2;

        for (int j = 0; j < n - 1; ++j) {
            i64 d = mat[i][j] - v;
            mat[i] [j] -= d;
            mat[i + 1][j] -= d;
            mat[i][j + 1] += d;
            mat[i + 1][j + 1] += d;
        }
    }

    if (std::count(mat[n - 1].begin(), mat[n - 1].end(), 0) != n) {
        std::cout << "No\n";
    } else {
        std::cout << "Yes\n";
    }

    return 0;
}
