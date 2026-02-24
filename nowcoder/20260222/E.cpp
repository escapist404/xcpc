#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    const int V = 1E6;
    std::vector<int> e(V + 1);
    for (int i = 1; i <= V; ++i) {
        if (i % 10 == 0) {
            continue;
        }
        auto s = std::to_string(i);
        std::reverse(s.begin(), s.end());
        auto ii = std::stoi(s);
        e[i] = ii;
    }

    auto solve = [&]() {
        int a, b, k;
        std::cin >> a >> b >> k;

        std::queue<int> queue;
        std::vector<int> dist(V + 1, 1E9);

        dist[a] = 0;
        queue.push(a);

        while (queue.empty() == false) {
            auto x = queue.front();
            queue.pop();
            if (e[x] != 0 && dist[e[x]] > dist[x] + 1) {
                dist[e[x]] = dist[x] + 1;
                queue.push(e[x]);
            }
            if (x + k <= V && dist[x + k] > dist[x] + 1) {
                dist[x + k] = dist[x] + 1;
                queue.push(x + k);
            }
        }

        if (dist[b] == 1E9) {
            std::cout << "-1\n";
        } else {
            std::cout << dist[b] << "\n";
        }
    };

    while (T--) {
        solve();
    }

    return 0;
}
