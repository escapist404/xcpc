#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    int target = 0;
    std::set<std::deque<int>> a;
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        target = std::max(target, k);
        std::deque<int> d(k);
        for (int j = 0; j < k; ++j) {
            std::cin >> d[j];
        }
        a.insert(d);
    }

    int cur = 0;
    std::deque<int> ans;
    while (cur < target) {
        auto choice = *a.begin();
        cur += choice.size();
        for (auto i : choice) {
            ans.push_back(i);
        }
        a.erase(a.begin());
        std::set<std::deque<int>> b;
        for (auto i : a) {
            for (int j = 0; j < (int)choice.size() && i.empty() == false; ++j) {
                i.pop_front();
            }
            if (i.empty() == true) {
                continue;
            }
            b.insert(i);
        }
        std::swap(a, b);
    }

    for (int i = 0; i < target; ++i) {
        std::cout << ans[i] << " \n"[i + 1 == target];
    }
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}