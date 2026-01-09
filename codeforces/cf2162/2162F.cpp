#include <bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> seg(m);
    std::map<int, int> cnt;
    std::vector<std::vector<int>> ord(n, std::vector<int>(m));

    for (int i = 0; i < n; ++i) {
        cnt[i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        auto& [l, r] = seg[i];
        std::cin >> l >> r;
        --l;
        for (int j = l; j < r; ++j) {
            ord[j][i] = 1;
            cnt[j]++;
        }
    }

    int res = m;
    std::vector<int> valid(m, 1);
    std::vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
        auto [idx, occ] = *cnt.begin();
        if (occ == res) {
            cnt.erase(cnt.begin());
            ans[idx] = i;
            int res = i + 1;
            for (int j = 0; j < n; ++j) {
                if (ans[j] == -1) {
                    ans[j] = res++;
                }
            }
            break;
        } else {
            auto [idx, occ] = *cnt.rbegin();
            cnt.erase(--cnt.end());
            ans[idx] = i;
            for (int j = 0; j < m; ++j) {
                if (ord[idx][j] == 0 && valid[j] == 1) {
                    valid[j] = 0;
                    --res;
                    auto [l, r] = seg[j];
                    for (int k = l; k < r; ++k) {
                        ord[k][j] = 0;
                        if (ans[k] == -1) {
                            cnt[k]--;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
}

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
