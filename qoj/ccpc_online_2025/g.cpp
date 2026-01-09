#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, q, b;
    std::cin >> n >> q;
    b = ceil(sqrt(n));

    std::vector<int> val(n), ord(n + 2 * q);
    for (int i = 0; i < n; ++i) {
        std::cin >> val[i];
        ord[i] = val[i];
    }

    std::vector<std::pair<int, int>> qry(q);
    for (int i = 0; i < q; ++i) {
        auto& [l, r] = qry[i];
        std::cin >> l >> r;
        ord[n + 2 * i] = l;
        ord[n + 2 * i + 1] = r;
    }

    std::sort(ord.begin(), ord.end());
    ord.erase(std::unique(ord.begin(), ord.end()), ord.end());
    int v = ord.size();

    for (int i = 0; i < n; ++i) {
        val[i] = std::lower_bound(ord.begin(), ord.end(), val[i]) - ord.begin();
    }
    for (int i = 0; i < q; ++i) {
        auto& [l, r] = qry[i];
        l = std::lower_bound(ord.begin(), ord.end(), l) - ord.begin();
        r = std::lower_bound(ord.begin(), ord.end(), r) - ord.begin();
    }
    
    std::vector<int> le, ge;
    std::vector<std::vector<int>> occ_le, occ_ge;
    std::vector<std::vector<i64>> pre;
    std::vector<int> cnt(v);

    for (int i = 0; i < n; ++i) {
        cnt[val[i]]++;
    }
    for (int i = 0; i < v; ++i) {
        if (cnt[i] <= b) {
            le.push_back(i);
        } else {
            ge.push_back(i);
        }
    }

    occ_le.resize(le.size());
    occ_ge.resize(ge.size(), std::vector<int>(n));
    pre.resize(ge.size(), std::vector<i64>(ge.size()));

    for (int i = 0; i < n; ++i) {
        if (cnt[val[i]] <= b) {
            int rk = std::lower_bound(le.begin(), le.end(), val[i]) - le.begin();
            occ_le[rk].push_back(i);
        } else {
            int rk = std::lower_bound(ge.begin(), ge.end(), val[i]) - ge.begin();                
            occ_ge[rk][i] = 1;
        }
    }

    for (auto& i : occ_ge) {
        for (int j = 1; j < n; ++j) {
            i[j] += i[j - 1];
        }
    }

    for (int y : ge) {
        int ry = std::lower_bound(ge.begin(), ge.end(), y) - ge.begin();
        int c = cnt[y];
        for (int i = 0; i < n; ++i) {
            if (cnt[val[i]] > b) {
                int rx = std::lower_bound(ge.begin(), ge.end(), val[i]) - ge.begin();
                if (val[i] == y) {
                    c--;
                }
                pre[rx][ry] += c;
            }
        }
    }
    
    
    for (int i = 0; i < q; ++i) {
        const auto [l, r] = qry[i];
        if (cnt[l] <= b && cnt[r] <= b) {
            int idx_l = 0, idx_r = 0;
            int rk_l = std::lower_bound(le.begin(), le.end(), l) - le.begin();
            int rk_r = std::lower_bound(le.begin(), le.end(), r) - le.begin();
            i64 ans = 0;
            while (idx_r < cnt[r]) {
                while (idx_l < cnt[l] && occ_le[rk_l][idx_l] < occ_le[rk_r][idx_r]) {
                    idx_l++;
                }
                ans += idx_l;
                idx_r++;
            }
            std::cout << ans << "\n";
        } else if (cnt[l] <= b && cnt[r] > b) {
            int rk_l = std::lower_bound(le.begin(), le.end(), l) - le.begin();
            int rk_r = std::lower_bound(ge.begin(), ge.end(), r) - ge.begin();
            i64 ans = 0;
            for (int idx : occ_le[rk_l]) {
                ans += occ_ge[rk_r].back() - occ_ge[rk_r][idx];
            }
            std::cout << ans << "\n";
        } else if (cnt[l] > b && cnt[r] <= b) {
            int rk_l = std::lower_bound(ge.begin(), ge.end(), l) - ge.begin();
            int rk_r = std::lower_bound(le.begin(), le.end(), r) - le.begin();
            i64 ans = 0;
            for (int idx : occ_le[rk_r]) {
                ans += occ_ge[rk_l][idx];
            }
            std::cout << ans << "\n";
        } else if (cnt[l] > b && cnt[r] > b) {
            int rk_l = std::lower_bound(ge.begin(), ge.end(), l) - ge.begin();
            int rk_r = std::lower_bound(ge.begin(), ge.end(), r) - ge.begin();
            std::cout << pre[rk_l][rk_r] << "\n";
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}