#include <bits/stdc++.h>

using i64 = long long;

template <typename T>
class MaxFlow {
    struct Edge {
        int to, next;
        T capacity;
        Edge(const int to = 0, const int next = -1, const T capacity = 0) : to(to), next(next), capacity(capacity) {}
    };

    int n;
    std::vector<Edge> edge;
    std::vector<int> head;

   public:
    MaxFlow(const int n) : n(n), head(n, -1) {}

    void add_edge(const int from, const int to, const T capacity) {
        edge.emplace_back(to, head[from], capacity);
        head[from] = edge.size() - 1;
        edge.emplace_back(from, head[to], 0);
        head[to] = edge.size() - 1;
    }

    T max_flow(const int s, const int t, const T max = std::numeric_limits<T>::max()) {
        std::vector<int> depth(n, -1), cur(n, -1);

        auto bfs = [&]() {
            std::queue<int> queue;
            std::fill(depth.begin(), depth.end(), -1);

            queue.emplace(s), depth[s] = 0;

            while (queue.size()) {
                int from = queue.front();
                queue.pop();

                for (int i = head[from]; ~i; i = edge[i].next) {
                    auto [to, next, capacity] = edge[i];
                    if (depth[to] == -1 && (capacity > 0)) {
                        depth[to] = depth[from] + 1;
                        queue.push(to);
                    }
                }
            }
            return depth[t];
        };

        auto dfs = [&](auto self, const int from, const T up) {
            if (from == t || up == 0) return up;
            T ret = 0;

            for (int& i = cur[from]; ~i; i = edge[i].next) {
                auto [to, next, capacity] = edge[i];
                if (depth[to] != depth[from] + 1) continue;

                auto further = self(self, to, std::min(up - ret, capacity));
                if (further) {
                    ret += further;
                    edge[i].capacity -= further;
                    edge[i ^ 1].capacity += further;
                }
            }
            return ret;
        };

        T flow = 0;
        while (~bfs()) {
            cur = head;
            flow += dfs(dfs, s, max - flow);
        }
        return flow;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::set<int> F;
    std::vector<std::pair<int, int>> P(N);
    for (auto& [X, R] : P) {
        std::cin >> X >> R;
        F.insert(X - R);
        F.insert(X + R);
    }

    std::vector<int> G(F.begin(), F.end());

    int M = G.size();

    MaxFlow<int> H(N + M + 2);
    int S = N + M;
    int T = N + M + 1;
    for (int i = 0; i < N; ++i) {
        H.add_edge(S, i, 1);
    }
    for (int i = N; i < N + M; ++i) {
        H.add_edge(i, T, 1);
    }
    for (int i = 0; i < N; ++i) {
        auto [X, R] = P[i];
        int a = std::lower_bound(G.begin(), G.end(), X - R) - G.begin() + N;
        int b = std::lower_bound(G.begin(), G.end(), X + R) - G.begin() + N;
        H.add_edge(i, a, 1);
        H.add_edge(i, b, 1);
    }

    std::cout << H.max_flow(S, T) << "\n";

    return 0;
}
