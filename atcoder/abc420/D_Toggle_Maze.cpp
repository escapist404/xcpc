#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

int main() {
    int H, W;
    std::cin >> H >> W;

    std::vector<std::string> matrix(H);
    for (int i = 0; i < H; ++i) {
        std::cin >> matrix[i];
    }

    auto id = [&](const int x, const int y, const bool d) {
        return x * W + y + (d ? H * W : 0);
    };

    auto valid = [&](const int x, const int y) {
        return 0 <= x && x < H && 0 <= y && y < W;
    };

    int S1, S2, G1, G2;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (matrix[i][j] == 'S') {
                S1 = id(i, j, 0);
                S2 = id(i, j, 1);
                matrix[i][j] = '.';
            }
            if (matrix[i][j] == 'G') {
                G1 = id(i, j, 0);
                G2 = id(i, j, 1);
                matrix[i][j] = '.';
            }
        }
    }
    const int dx[] = {0, 1}, dy[] = {1, 0};

    std::vector<std::vector<std::pair<int, int>>> adj(H * W * 2);

    auto add = [&](const int u, const int v, const int w) {
        adj[u].emplace_back(v, w);
    };

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            for (int t = 0; t < 2; ++t) {
                if (valid(i + dx[t], j + dy[t])) {
                    char uc = matrix[i][j], vc = matrix[i + dx[t]][j + dy[t]];
                    int u[] = {id(i, j, 0), id(i, j, 1)};
                    int v[] = {id(i + dx[t], j + dy[t], 0), id(i + dx[t], j + dy[t], 1)};
                    if (uc == '.') {
                        if (vc == '.') {
                            add(u[0], v[0], 1);
                            add(v[0], u[0], 1);
                            add(u[1], v[1], 1);
                            add(v[1], u[1], 1);
                        } else if (vc == '?') {
                            add(u[0], v[1], 1);
                            add(v[1], u[1], 1);
                            add(u[1], v[0], 1);
                            add(v[0], u[0], 1);
                        } else if (vc == 'o') {
                            add(u[0], v[0], 1);
                            add(v[0], u[0], 1);
                        } else if (vc == 'x') {
                            add(u[1], v[1], 1);
                            add(v[1], u[1], 1);
                        }
                    } else if (uc == '?') {
                        if (vc == '.') {
                            add(u[0], v[0], 1);
                            add(v[0], u[1], 1);
                            add(u[1], v[1], 1);
                            add(v[1], u[0], 1);
                        } else if (vc == '?') {
                            add(u[0], v[1], 1);
                            add(v[1], u[0], 1);
                            add(u[1], v[0], 1);
                            add(v[0], u[1], 1);
                        } else if (vc == 'o') {
                            add(u[0], v[0], 1);
                            add(v[0], u[1], 1);
                        } else if (vc == 'x') {
                            add(u[1], v[1], 1);
                            add(v[1], u[0], 1);
                        }
                    } else if (uc == 'o') {
                        if (vc == '.') {
                            add(u[0], v[0], 1);
                            add(v[0], u[0], 1);
                        } else if (vc == '?') {
                            add(u[0], v[1], 1);
                            add(v[0], u[0], 1);
                        } else if (vc == 'o') {
                            add(u[0], v[0], 1);
                            add(v[0], u[0], 1);
                        }
                    } else if (uc == 'x') {
                        if (vc == '.') {
                            add(u[1], v[1], 1);
                            add(v[1], u[1], 1);
                        } else if (vc == '?') {
                            add(u[1], v[0], 1);
                            add(v[1], u[1], 1);
                        } else if (vc == 'x') {
                            add(u[1], v[1], 1);
                            add(v[1], u[1], 1);
                        }
                    }
                }
            }        
        }
    }

    std::queue<int> queue;
    std::vector<int> dis(2 * H * W, 1e9);

    queue.push(S1);
    dis[S1] = 0;

    while (queue.size()) {
        int u = queue.front();
        queue.pop();

        for (const auto [v, w] : adj[u]) {
            if (dis[v] == 1e9) {
                dis[v] = dis[u] + w;
                queue.push(v);
            }
        }
    }

    if (std::min(dis[G1], dis[G2]) != 1e9) {
        std::cout << std::min(dis[G1], dis[G2]) << "\n";
    } else {
        std::cout << -1 << "\n";
    }
}
