#include <bits/stdc++.h>

using i64 = long long;

struct DisjointSetUnion {
    std::vector<int> data;
    int get(int x) {
        return data[x] < 0 ? x : data[x] = get(data[x]);
    }
    bool connected(int u, int v) {
        return get(u) == get(v);
    }
    void merge(int u, int v) {
        if (connected(u, v)) {
            return;
        }
        u = data[u];
        v = data[v];
        if (data[u] > data[v]) {
            std::swap(u, v);
        }
        data[u] += data[v];
        data[v] = 0;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    std::vector<std::tuple<int, int, int>> edges(M);
    for (int i = 0; i < M; )

    return 0;
}
