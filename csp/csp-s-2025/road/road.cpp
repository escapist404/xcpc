#include <bits/stdc++.h>

using i64 = long long;

struct DisjointSetUnion {
    std::vector<int> data;
    DisjointSetUnion(const int n) : data(n, -1) {}

    int get(int x) {
        return data[x] < 0 ? x : data[x] = get(data[x]);
    }
    int size(int x) {
        return -data[get(x)];
    }
    bool isconnected(int x, int y) {
        return get(x) == get(y);
    }
    bool connect(int x, int y) {
        if (isconnected(x, y)) {
            return false;
        }
        int u = get(x);
        int v = get(y);
        if (data[u] > data[v]) {
            std::swap(u, v);
        }
        data[u] += data[v];
        data[v] = u;
        return true;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::tuple<int, int, int>> edges(m);
    for (auto& [u, v, w] : edges) {
        std::cin >> u >> v >> w;
        --u, --v;
    }

    // {
    //     std::vector<std::tuple<int, int, int>> valid_edges;
    //     valid_edges.reserve(n - 1);
    //     DisjointSetUnion D(n);
    //     for (auto [u, v, w] : edges) {
    //         if (D.connect(u, v)) {
    //             valid_edges.emplace_back(u, v, w);
    //         }
    //     }
    //     edges = valid_edges;
    // }
    
    std::vector<int> c(k);
    std::vector<std::vector<int>> a(k, std::vector<int>(n));
    for (int i = 0; i < k; ++i) {
        std::cin >> c[i];
        for (int j = 0; j < n; ++j) {
            int x;
            std::cin >> x;
            edges.emplace_back(n + i, j, x);
        }
    }

    std::sort(edges.begin(), edges.end(), [](auto x, auto y) {
        return std::get<2>(x) < std::get<2>(y);
    });
    
    i64 ans = 9E18;
    for (int S = 0; S < (1 << k); ++S) {
        int s = n + __builtin_popcount(S);
        i64 cur = 0;
        std::vector<int> mapping(k, -1);
        for (int i = 0, j = 0; i < k; ++i) {
            if ((S >> i) & 1) {
                cur += c[i];
                mapping[i] = j++;
            }
        }

        int count = 0;
        DisjointSetUnion D(s);
        for (auto [u, v, w] : edges) {
            if (u >= n) {
                if (mapping[u - n] == -1) {
                    continue;
                }
                u = n + mapping[u - n];
            }
            if (D.connect(u, v)) {
                cur += w;
                ++count;
            }
            if (count == s - 1) {
                break;
            }
        }

        ans = std::min(ans, cur);
    }

    std::cout << ans << "\n";
    return 0;
}
