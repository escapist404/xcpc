#include <bits/stdc++.h>

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> ref = a;
    std::sort(ref.begin(), ref.end());
    ref.erase(std::unique(ref.begin(), ref.end()), ref.end());

    for (int& i : a) {
        i = std::lower_bound(ref.begin(), ref.end(), i) - ref.begin();
    }

    int m = ref.size();
    int b = ceil(sqrt(n));
    std::vector<int> im;
    {
        std::vector<int> cnt(m);
        for (int i = 0; i < n; ++i) {
            cnt[a[i]]++;
        }
    
        for (int i = 0; i < m; ++i) {
            if (cnt[i] >= b) {
                im.push_back(i);
            }
        }
    }

    std::vector<std::pair<int, int>> ans(q, {1000000001, 1000000001}), qry(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        --l;
        qry[i] = {l, r};
    }

    auto insert_ans = [](std::pair<int, int>& ans, int val) {
        if (ans.first == 1000000001) {
            ans.first = val;
        } else {
            if (ans.first != val) {
                if (ans.second == 1000000001) {
                    ans.second = val;
                }
            }
        }
    };

    std::vector<int> cnt;
    for (int i = 0; i < (int)im.size(); ++i) {
        cnt.assign(n + 1, 0);
        for (int j = 0; j < n; ++j) {
            if (a[j] == im[i]) {
                cnt[j + 1] = 1;
            }
            cnt[j + 1] += cnt[j];
        }

        for (int j = 0; j < q; ++j) {
            auto [l, r] = qry[j];
            int g = (r - l) / 3;
            if (cnt[r] - cnt[l] > g) {
                insert_ans(ans[j], ref[im[i]]);
            }
        }
    }

    cnt.assign(m, 0);
    for (int i = 0; i < q; ++i) {
        auto [l, r] = qry[i];
        int g = (r - l) / 3;
        if (g < b) {
            for (int j = l; j < r; ++j) {
                cnt[a[j]]++;
                if (cnt[a[j]] > g) {
                    insert_ans(ans[i], ref[a[j]]);
                }
            }
            for (int j = l; j < r; ++j) {
                cnt[a[j]]--;
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        if (ans[i].first > ans[i].second) {
            std::swap(ans[i].first, ans[i].second);
        }
        if (ans[i].first == 1000000001) {
            std::cout << "-1\n";
        } else if (ans[i].second == 1000000001) {
            std::cout << ans[i].first << "\n";
        } else {
            std::cout << ans[i].first << " " << ans[i].second << "\n";
        }
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