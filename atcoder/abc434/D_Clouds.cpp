#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

const int W = 2000;
std::array<std::array<u64, W + 1>, W + 1> c;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::mt19937_64 rnd(time(0));
    std::unordered_map<u64, int> ref;

    for (int i = 0; i < N; ++i) {
        int u, d, l, r;
        std::cin >> u >> d >> l >> r;
        --u, --l;
        u64 w = rnd();
        ref[w] = i;
        c[u][l] += w;
        c[u][r] -= w;
        c[d][l] -= w;
        c[d][r] += w;
    }

    for (int i = 1; i <= W; ++i) {
        for (int j = 0; j <= W; ++j) {
            c[i][j] += c[i - 1][j];
        }
    }
    for (int i = 0; i <= W; ++i) {
        for (int j = 1; j <= W; ++j) {
            c[i][j] += c[i][j - 1];
        }
    }

    int all = 0;
    std::vector<int> only(N);
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < W; ++j) {
            if (c[i][j] == 0) {
                all++;
            } else if (ref.count(c[i][j])) {
                only[ref[c[i][j]]]++;
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        std::cout << all + only[i] << "\n";
    }

    return 0;
}
