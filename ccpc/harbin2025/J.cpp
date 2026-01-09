#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    auto c = a;
    std::vector<i64> x(m + n), t(m + n);
    for (int i = 0; i < m; ++i) {
        std::cin >> x[i] >> t[i];
        --t[i];
    }
    for (int i = m; i < m + n; ++i) {
        x[i] = 1E18;
        t[i] = i - m;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i = 0; i < m + n; ++i) {
        pq.push(i);
    }

    std::vector<std::vector<int>> f(n);
    for (int i = 0; i < m + n; ++i) {
        f[t[i]].push_back(i);
    }

    std::vector<int> vis(n, 1);

    i64 s = 0;
    for (int i = 0; i < m + n; ++i) {
        i64 d = x[i] - s;

        while (d && pq.size()) {
            int u = pq.top();
            if (u < i) {
                pq.pop();
                continue;
            }
            i64 r = std::min(d, (i64)c[t[u]]);

            d -= r;
            s += r;
            c[t[u]] -= r;

            if (c[t[u]] == 0) {
                pq.pop();
                vis[t[u]] = 0;
            }
        }

        if (d) {
            break;
        } else {
            c[t[i]] = a[t[i]];
            if (vis[t[i]] == 0) {
                pq.push(*std::upper_bound(f[t[i]].begin(), f[t[i]].end(), i));
            }
        }
    }

    std::cout << s << "\n";
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