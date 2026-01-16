#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a, --b;

        if (a == -1 && b == -1) {
            adj[n].push_back(i);
        } else {
            adj[a].push_back(i);
            adj[b].push_back(i);
        }
    }

    std::queue<int> queue;
    std::vector<int> vis(n + 1);

    queue.push(n);
    while (queue.empty() == false) {
        auto x = queue.front();
        queue.pop();

        if (vis[x] == true) {
            continue;
        }

        vis[x] = true;
        for (const auto& i : adj[x]) {
            queue.push(i);
        }
    }

    std::cout << std::count(vis.begin(), vis.begin() + n, 1) << "\n";

    return 0;
}