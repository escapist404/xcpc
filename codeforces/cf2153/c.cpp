#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    using i64 = long long;
    i64 ans = 0;
    int count = 0;
    std::set<int, std::greater<int>> s;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        if (s.count(v)) {
            s.erase(v);
            ans += 2 * v;
            count += 2;
        } else {
            s.insert(v);
        }
    }

    if (count == 0) {
        std::cout << 0 << "\n";
        return;
    }

    std::vector<int> r(s.begin(), s.end());
    int m = r.size();
    i64 cand = 0;
    for (int i = 0; i < m - 1; ++i) {
        if (r[i] < r[i + 1] + ans) {
            cand = std::max(cand, (i64)r[i] + r[i + 1]);
        }
    }

    if (r.empty() == false && r.back() < ans) {
        cand = std::max(cand, (i64)r.back());
    }

    if (cand == 0) {
        if (count == 2) {
            ans = 0;
        }
    }

    ans += cand;
    std::cout << ans << "\n";
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
