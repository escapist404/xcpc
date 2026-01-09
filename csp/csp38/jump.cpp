#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;

    int x, y;
    std::cin >> x >> y;
    --x, --y;

    std::map<std::pair<int, int>, int> dis;
    std::queue<std::pair<int, int>> queue;

    const std::vector<std::pair<int, int>> cand = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

    queue.push({x, y});
    dis[{x, y}] = 0;
    while (queue.size()) {
        auto [x, y] = queue.front();
        queue.pop();

        if (dis[{x, y}] == k) {
            continue;
        }

        for (auto [u, v] : cand) {
            if (0 <= x + u && x + u < n && 0 <= y + v && y + v < n) {
                if (dis.count({x + u, y + v})) {
                    continue;
                }
                dis[{x + u, y + v}] = dis[{x, y}] + 1;
                queue.push({x + u, y + v});
            }
        }
    }

    std::cout << dis.size() << "\n";

    return 0;
}