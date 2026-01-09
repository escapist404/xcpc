#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::sort(a.begin(), a.end());

    if (k / a[0] > n) {
        std::cout << -1 << "\n";
        return;
    }

    std::map<int, int> count;
    std::set<int> s(a.begin(), a.end());

    std::vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (count[a[i]] == 0) {
            ans.push_back(a[i]);
            for (int j = 1; 1LL * j * a[i] <= k; ++j) {
                if (s.count(j * a[i]) == 0) {
                    std::cout << -1 << "\n";
                    return;
                }
                count[j * a[i]]++;
            }
        }
    }

    std::cout << ans.size() << "\n";
    for (int i = 0; i < (int)ans.size(); ++i) {
        std::cout << ans[i] << " \n"[i == (int)ans.size() - 1];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}