#include <bits/stdc++.h>

using i64 = long long;

const int W = 4;
const int C = 16;
const int N = 1 << C;
const int VN = N / 2;
const int MASK_LEN[W] = {4, 2, 2, 1};
const int MASK[W][4] = {{1, 2, 4, 8}, {3, 12}, {5, 10}, {15}};

void solve(const std::vector<i64>& dis) {
    int n, S = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string s, t;
        std::cin >> s >> t;
        t += s;
        int d = std::stoi(t, 0, 2);
        S ^= 1 << d;
    }

    std::cout << dis[S] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    int a[W];
    std::cin >> a[0] >> a[1] >> a[2] >> a[3];

    std::vector<std::vector<std::pair<int, i64>>> adj(N);

    for (int S = 1; S < N; ++S) {
        for (int i = 0; i < W; ++i) {
            for (int j = 0; j < MASK_LEN[i]; ++j) {
                int SS = 0;
                for (int k = 0; k < C; ++k) {
                    if ((S >> k) & 1) {
                        SS ^= 1 << (k ^ MASK[i][j]);
                    }
                }
                adj[SS & (VN - 1)].emplace_back(S, a[i]);
            }
        }
    }

    std::vector<i64> dis(N, -1);
    std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<std::pair<i64, int>>> queue;
    queue.emplace(0, 0);
    while (queue.empty() == false) {
        auto [d, u] = queue.top();
        queue.pop();
        if (dis[u] != -1) {
            continue;
        }
        dis[u] = d;
        for (auto [v, w] : adj[u]) {
            queue.emplace(w + d, v);                
        }
    }

    while (T--) {
        solve(dis);
    }

    return 0;
}