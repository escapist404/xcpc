#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x, --y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    std::vector<int> father(n);
    father[0] = -1;
    auto recursion = [&](auto& self, int x) -> void {
        for (auto i : adj[x]) {
            if (i == father[x]) {
                continue;
            }
            father[i] = x;
            self(self, i);
        }
    };

    recursion(recursion, 0);

    int ans = 1, last = 1, cur = 1;
    std::vector<int> set = adj[0];
    std::vector<int> valid = {0};
    std::vector<int> op(n, -1);
    op[0] = 0;
    while (set.size()) {
        cur = set.size();
        if (last == 1) {
            int j = 0;
            for (int i = 0; i < ans; ++i) {
                if (j == cur) {
                    break;
                }
                if (i == op[valid.front()]) {
                    continue;
                }
                op[set[j++]] = i;
            }
            while (j < cur) {
                op[set[j++]] = ans++;
            }
        } else {
            std::sort(valid.begin(), valid.end());
            std::vector<int> sgn(last);
            for (int i = 0; i < cur; ++i) {
                int ref = std::lower_bound(valid.begin(), valid.end(), father[set[i]]) - valid.begin();
                (ref += 1) %= last;
                if (sgn[ref] == 1) {
                    continue;
                } else {
                    op[set[i]] = op[valid[ref]];
                    sgn[ref] = 1;
                }
            }
            sgn = std::vector<int>(ans);
            for (auto i : valid) {
                sgn[op[i]] = 1;
            }
            int j = 0;
            for (int i = 0; i < ans; ++i) {
                if (j == cur) {
                    break;
                }
                if (op[set[j]] != -1) {
                    j++;
                    i--;
                    continue;
                }
                if (sgn[i] == 1) {
                    continue;
                }
                op[set[j++]] = i;
            }
            while (j < cur) {
                if (op[set[j]] != -1) {
                    j++;
                    continue;
                }
                op[set[j++]] = ans++;
            }
        }
        std::vector<int> next;
        last = 0;
        valid.clear();
        for (auto i : set) {
            bool ok = false;
            for (auto j : adj[i]) {
                if (father[i] == j) {
                    continue;
                }
                next.push_back(j);
                ok = true;
            }
            last += ok;
            if (ok) {
                valid.push_back(i);
            }
        }
        set = next;
    }

    std::vector<std::set<int>> out(ans);
    for (int i = 0; i < n; ++i) {
        assert(op[i] != -1);
        out[op[i]].insert(i);
    }

    std::cout << ans << "\n";
    for (auto s : out) {
        std::cout << s.size() << " ";
        for (auto i : s) {
            std::cout << i + 1 << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int tt;
    std::cin >> tt;

    while (tt--) {
        solve();
    }

    return 0;
}