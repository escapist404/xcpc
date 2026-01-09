#include <bits/stdc++.h>

const int Q = 9, N = 500;

using i64 = long long;

constexpr std::array<int, N + 1> make_log2n() {
    std::array<int, N + 1> arr{};
    arr[1] = 0;
    arr[2] = 1;
    for (int i = 3; i <= N; ++i) {
        arr[i] = arr[i / 2] + 1;
    }
    return arr;
}

auto log2n = make_log2n();

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> A(n, std::vector<int>(m));

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < m; ++j) {
            A[i][j] = s[j] - '0';
        }
    }

    auto turn = [](int n, int m, const std::vector<std::vector<int>>& A) {
        std::vector<std::vector<int>> B(m, std::vector<int>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                B[i][j] = A[j][i];
            }
        }
        return B;
    };

    bool T = false;
    if (n > m) {
        T = true;
        A = turn(n, m, A);
        std::swap(n, m);
    }

    std::vector<std::vector<std::vector<int>>> s(m, std::vector<std::vector<int>>(n, std::vector<int>(Q + 1, 1E9)));

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int last = -1;
            for (int k = 0; k < m; ++k) {
                if (A[i][k] == 1 && A[j][k] == 1) {
                    if (last != -1) {
                        int v = (k + 1 - last) * (j - i + 1);
                        int z = log2n[j + 1 - i], y = 1 << z;
                        for (int c = last; c <= k; ++c) {
                            s[c][i][z] = std::min(s[c][i][z], v);
                            s[c][j + 1 - y][z] = std::min(s[c][j + 1 - y][z], v);
                        }
                    }
                    last = k;
                }
            }
        }
    }

    std::vector<std::vector<int>> B(n, std::vector<int>(m));
    for (int j = 0; j < m; ++j) {
        for (int k = Q; k >= 1; --k) {
            for (int i = 0; i < n; ++i) {
                s[j][i][k - 1] = std::min(s[j][i][k - 1], s[j][i][k]);
                if (i + (1 << (k - 1)) < n) {
                    s[j][i + (1 << (k - 1))][k - 1] = std::min(s[j][i + (1 << (k - 1))][k - 1], s[j][i][k]);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            B[i][j] = s[j][i][0];
            if (s[j][i][0] == 1E9) {
                B[i][j] = 0;
            }
        }
    }

    if (T == true) {
        B = turn(n, m, B);
        std::swap(n, m);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << B[i][j] << " \n"[j == m - 1];
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
