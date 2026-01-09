#include <bits/stdc++.h>

void solve() {
    int n, k, m;
    std::cin >> n >> m >> k;

    std::vector<int> c(k);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        --x;
        c[x] = 1;
    }

    int cur = 0, ans = 0;
    std::vector<int> d(k);
    std::map<std::pair<int, int>, int> e;
    std::vector<std::vector<int>> ed(k);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a, --b;
        if (a == b) {
            if (c[a] == 1) {
                ++cur;
            } else {
                d[a]++;
            }
            continue;
        }
        if (a > b) {
            std::swap(a, b);
        }

        if (c[a] == 0 && c[b] == 0) {
            e[{a, b}]++;
            ed[a].push_back(b);
            ed[b].push_back(a);
        }
        if (c[a] == 0 && c[b] == 1) {
            d[a]++;
        }
        if (c[a] == 1 && c[b] == 0) {
            d[b]++;
        }
        if (c[a] == 1 && c[b] == 1) {
            cur++;
        }
    }

    for (int i = 0; i < k; ++i) {
        std::sort(ed[i].begin(), ed[i].end());
        ed[i].erase(std::unique(ed[i].begin(), ed[i].end()), ed[i].end());
    }

    ans = cur;
    for (auto [ed, cnt] : e) {
        auto [u, v] = ed;
        ans = std::max(ans, cur + d[u] + d[v] + cnt);
    }
    
    std::set<std::pair<int, int>, std::greater<std::pair<int, int>>> set;
    for (int i = 0; i < k; ++i) {
        if (c[i] == 1) {
            continue;
        }
        set.insert({d[i], i});
    }

    for (int i = 0; i < k; ++i) {
        if (c[i] == 1) {
            continue;
        }

        ans = std::max(ans, cur + d[i]);

        set.erase({d[i], i});
        for (auto v : ed[i]) {
            set.erase({d[v], v});
        }

        if (set.empty() == false) {
            ans = std::max(ans, cur + d[i] + (*set.begin()).first);
        }

        set.insert({d[i], i});
        for (auto v : ed[i]) {
            set.insert({d[v], v});
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
