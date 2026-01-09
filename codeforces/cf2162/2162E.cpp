#include <bits/stdc++.h>

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::set<int> s(a.begin(), a.end());
    if (s.size() != n) {
        std::vector<int> ans;
        for (int i = 1; i <= n && k > 0; ++i) {
            if (s.count(i) == 0) {
                ans.push_back(i);
            }
        }
        if (ans.size() == 1) {
            if (a[n - 1] == a[n - 2]) {
                ans.push_back(a[n - 3]);
                ans.push_back(a[n - 2]);
            } else {
                ans.push_back(a[n - 2]);
                ans.push_back(a[n - 1]);
            }
        } else if (ans.size() == 2) {
            ans.push_back(a[0]);
        }
        for (int i = 0; k > 0; ++i) {
            if (i == 3) {
                i = 0;
            }
            std::cout << ans[i] << " ";
            --k;
        }
        std::cout << "\n";
    } else {
        for (int i = 0; i < k; ++i) {
            std::cout << a[i] << " \n"[i == k - 1];
        }
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