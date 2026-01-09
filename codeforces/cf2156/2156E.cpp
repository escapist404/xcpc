#include <bits/stdc++.h>

using i64 = long long;

const int CAND_SIZE = 3;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<std::vector<int>> min(n);
    {
        std::vector<int> cur;
        cur = std::vector<int>(CAND_SIZE, -1);
        for (int i = 0; i < n; ++i) {
            min[i] = cur;
            for (int j = 0; j < CAND_SIZE; ++j) {
                if (cur[j] == -1 || a[cur[j]] >= a[i]) {
                    cur.insert(cur.begin() + j, i);
                    break;
                }
            }
            if (cur.size() > CAND_SIZE) {
                cur.pop_back();
            }
        }
    }

    int L = -1E9, R = 1E9;
    while (L + 1 < R) {
        int C = (L + R) >> 1;
        bool ok = [&](int C) -> bool {
            std::vector<int> deg(n);
            std::vector<std::vector<int>> adj(n);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < CAND_SIZE; ++j) {
                    if (min[i][j] != -1 && a[i] - a[min[i][j]] >= C) {
                        adj[i].push_back(min[i][j]);
                        deg[i]++;
                        adj[min[i][j]].push_back(i);
                        deg[min[i][j]]++;
                    }
                }
            }

            int count = std::count_if(deg.begin(), deg.end(), [](int x) { return x >= 2; });
    
            for (int u = 0; u < n; ++u) {
                int cur = deg[u] >= 2;
                for (const auto& v : adj[u]) {
                    if (deg[v] == 2) {
                        ++cur;
                    }
                }
                if (cur == count) {
                    return false;
                }
            }

            return true;
        }(C);

        if (ok) {
            L = C;
        } else {
            R = C;
        }
    }

    std::cout << L << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}