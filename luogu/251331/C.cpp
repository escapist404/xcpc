#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using i64 = long long;
const i64 INF = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> e(3 * n);
    for (int i = 0; i < 3 * n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    /*
        选 3 个结点染色后，仅在 3 个结点的 LCA 到根的链上不产生代价。要使代价最小，就要让链上亏损的贡献尽量大。
        s[i][0/1/2] 代表以结点 i 为根的子树内，剩下了 0/1/2 个结点没有上色，此时最大的亏损贡献。
        令 v 是 i 的儿子，s[i][(sum(x) + 1) mod 3] = s[v][x] + ceil(sum(x) / 3) * d[i].
        实现上考虑遍历 v，记 f'[i][0/1/2] 为考虑了 v 的贡献时的 f[i]。
        s'[i][0] = max(s[i][0] + s[v][0], s[i][2] + s[v][1] + d[i], s[i][1] + s[v][2] + d[i])
        s'[i][1] = max(s[i][0] + s[v][1], s[i][1] + s[v][0], s[i][2] + s[v][2] + d[i])
        s'[i][2] = max(s[i][0] + s[v][2], s[i][1] + s[v][1], s[i][2] + s[v][0])
        令 s = s' 即完成转移。
        最后 3 * n * n - s[0][0] 即为答案。
    */

    auto find_loss = [&](auto& self, const int u, const int f, const int d) -> std::tuple<i64, i64, i64> {
        i64 s0 = -INF, s1 = 0, s2 = -INF;
        for (const auto v : e[u]) {
            if (v == f) {
                continue;
            }
            auto [t0, t1, t2] = self(self, v, u, d + 1);
            i64 a0 = std::max({s0 + t0, s1 + t2 + d, s2 + t1 + d});
            i64 a1 = std::max({s0 + t1, s1 + t0, s2 + t2 + d});
            i64 a2 = std::max({s0 + t2, s1 + t1, s2 + t0});
            std::tie(s0, s1, s2) = std::make_tuple(a0, a1, a2);
        }
        return std::make_tuple(s0, s1, s2);
    };

    for (int i = 0; i < 3 * n; ++i) {
        std::cout << 3LL * n * n - std::get<0>(find_loss(find_loss, i, -1, 1)) << " 0\n";
    }
    return 0;
}
