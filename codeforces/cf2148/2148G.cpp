#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> ans(n);
    std::map<int, int> map;
    std::vector<int> res;
    std::vector<int> vis(n + 1);
    for (int i = 0; i < n; ++i) {
        if (i != 0) {
            ans[i] = ans[i - 1];
        }
        
        std::vector<int> nres;
        for (int j = 1; j * j <= a[i]; ++j) {
            if (a[i] % j == 0) {
                map[j]++;
                if (map[j] != i + 1) {
                    ans[i] = std::max(ans[i], map[j]);
                } else if (vis[j] == false) {
                    nres.push_back(j);
                    vis[j] = true;
                }
                if (j * j != a[i]) {
                    map[a[i] / j]++;
                    if (map[a[i] / j] != i + 1) {
                        ans[i] = std::max(ans[i], map[a[i] / j]);
                    } else if (vis[a[i] / j] == false) {
                        nres.push_back(a[i] / j);
                        vis[a[i] / j] = true;
                    }
                }
            }
        }

        for (auto j : res) {
            if (map[j] != i + 1) {
                ans[i] = std::max(map[j], ans[i]);
                vis[j] = false;
            } else {
                nres.push_back(j);
            }
        }

        std::swap(res, nres);
    }

    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << " \n"[i + 1 == n];
    }
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}