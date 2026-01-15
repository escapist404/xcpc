#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <deque>

const int B = 20;
const int M = (1 << B) - 1;
const int C = 26;
const std::pair<int, int> orient[] = {std::make_pair(1, 0), std::make_pair(-1, 0), std::make_pair(0, 1), std::make_pair(0, -1)};

int main() {
    int h, w;
    std::cin >> h >> w;

    std::vector<std::vector<int>> adj(h * w + C);
    std::vector<std::string> mat(h);
    for (int i = 0; i < h; ++i) {
        std::cin >> mat[i];
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (mat[i][j] == '#') {
                continue;
            }
            int f = i * w + j;
            if (isalpha(mat[i][j])) {
                int tr = h * w + mat[i][j] - 'a';
                adj[f].push_back(tr + (1 << B));
                adj[tr].push_back(f);
            }
            for (auto [dx, dy] : orient) {
                int x = i + dx;
                int y = j + dy;
                if (x < 0 || x >= h || y < 0 || y >= w) {
                    continue;
                }
                if (mat[x][y] == '#') {
                    continue;
                }
                int t = x * w + y;
                adj[f].push_back(t);
            }
        }
    }

    std::vector<int> dis(h * w + C, -1);
    std::deque<int> deque = {0};
    dis[0] = 0;
    while (deque.empty() == false) {
        int u = deque.front();
        deque.pop_front();
        for (auto i : adj[u]) {
            int v = i & M;
            int w = (i >> B) == 0;
            if (dis[v] != -1) {
                continue;
            }
            dis[v] = dis[u] + w;
            if (w) {
                deque.push_back(v);
            } else {
                deque.push_front(v);
            }
        }
    }

    std::cout << dis[h * w - 1] << "\n";

    return 0;
}
