#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int H, W;
    std::cin >> H >> W;

    std::vector<std::string> U(H);
    for (int i = 0; i < H; ++i) {
        std::cin >> U[i];
    }

    int K = (H + 1) * W + H * (W + 1);
    int K1 = (H + 1) * W;

    
    std::vector<std::vector<std::pair<int, int>>> adj(K);
    auto add = [&](int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    };

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            int up = i * W + j;
            int dn = (i + 1) * W + j;
            int lf = i * (W + 1) + j + K1;
            int rt = i * (W + 1) + j + 1 + K1;

            add(up, dn, U[i][j] != 'A');
            add(lf, rt, U[i][j] != 'A');
            add(up, rt, U[i][j] != 'B');
            add(lf, dn, U[i][j] != 'B');
            add(up, lf, U[i][j] != 'C');
            add(rt, dn, U[i][j] != 'C');
        }
    }

    int S = K1;
    std::deque<std::pair<int, int>> q = {{S, 0}};
    std::vector<int> d(K, -1);

    while (q.size()) {
        auto [u, c] = q.front();
        q.pop_front();
        if (d[u] != -1) {
            continue;
        }
        d[u] = c;
        for (auto [v, w] : adj[u]) {
            if (w == 0) {
                q.emplace_front(v, c + w);
            } else {
                q.emplace_back(v, c + w);
            }
        }
    }

    std::cout << d[K - 1] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}