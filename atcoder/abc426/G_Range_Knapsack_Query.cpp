#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> w(n);
    std::vector<i64> v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> w[i] >> v[i];
    }

    int q;
    std::cin >> q;

    std::vector<int> l(q), r(q), c(q);
    for (int i = 0; i < q; ++i) {
        std::cin >> l[i] >> r[i] >> c[i];
        --l[i];
    }
    auto b = *std::max_element(c.begin(), c.end());

    std::vector<i64> ans(q);
    auto count_interval = [&](auto& self, int L, int R, const std::vector<int>& D) -> void {
        if (D.empty()) {
            return;
        }
        if (R - L == 1) {
            for (auto i : D) {
                ans[i] = c[i] >= w[L] ? v[L] : 0;
            }
            return;
        }
        int M = (L + R) / 2;
        
        std::vector<std::vector<i64>> f(M - L + 1, std::vector<i64>(b + 1));
        std::vector<std::vector<i64>> g(R - M + 1, std::vector<i64>(b + 1));

        for (int i = M - 1; i >= L; --i) {
            f[M - i] = f[M - i - 1];
            for (int j = w[i]; j <= b; ++j) {
                f[M - i][j] = std::max(f[M - i - 1][j - w[i]] + v[i], f[M - i][j]);
            }
        }
        for (int i = M; i < R; ++i) {
            g[i - M + 1] = g[i - M];
            for (int j = w[i]; j <= b; ++j) {
                g[i - M + 1][j] = std::max(g[i - M][j - w[i]] + v[i], g[i - M + 1][j]);
            }
        }

        std::vector<int> DL, DR;
        for (auto i : D) {
            if (l[i] < M && r[i] >= M) {
                for (int j = 0; j <= c[i]; ++j) {
                    ans[i] = std::max(ans[i], f[M - l[i]][j] + g[r[i] - M][c[i] - j]);
                }
            } else if (l[i] >= M) {
                DR.push_back(i);
            } else {
                DL.push_back(i);
            }
        }

        self(self, L, M, DL);
        self(self, M, R, DR);
    };

    {
        std::vector<int> temp(q);
        std::iota(temp.begin(), temp.end(), 0);
        count_interval(count_interval, 0, n, temp);
    }

    for (int i = 0; i < q; ++i) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}
