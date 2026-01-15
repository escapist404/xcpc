#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using i64 = long long;

void solve() {
    int n, m;
    i64 k;
    std::cin >> n >> m >> k;

    std::vector<int> f(m);
    for (int i = 0; i < m; ++i) {
        int a;
        std::cin >> a;
        --a;
        f[a]++;
    }

    std::vector<std::vector<int>> g(m);
    for (int i = 0; i < n; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        k -= y;
        --x;
        int d = z - y;
        g[x].push_back(d);
    }

    int x = 0;
    std::multiset<int> s;
    for (int i = m - 1; i >= 0; --i) {
        x += f[i];
        for (int j = 0; j < (int)g[i].size(); ++j) {
            s.insert(g[i][j]);
            if (s.size() > x) {
                s.erase(s.begin());
            }
        }
    }

    std::vector<int> c;
    int ans = s.size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < (int)g[i].size(); ++j) {
            auto it = s.find(g[i][j]);
            if (it == s.end()) {
                c.push_back(g[i][j]);
            } else {
                s.erase(it);
            }
        }
    }

    std::sort(c.begin(), c.end());
    for (int i = 0; i < (int)c.size(); ++i) {
        if (k < c[i]) {
            break;
        } else {
            k -= c[i];
            ++ans;
        }
    }

    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}
