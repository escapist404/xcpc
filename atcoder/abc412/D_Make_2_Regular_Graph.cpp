#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> adj(N, std::vector<int>(N));

    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    std::vector<int> f(1 << N);

    for (int S = 0; S < (1 << N); ++S) {
        
    }
}