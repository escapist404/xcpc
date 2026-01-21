#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> d[3];
    int count[3] = {0, 0, 0};
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        int cand[3];
        std::cin >> cand[0] >> cand[1] >> cand[2];
        auto it = std::max_element(cand, cand + 3);
        int ref = it - cand;
        ans += *it;
        count[ref]++;
        std::swap(cand[0], cand[it - cand]);
        d[ref].push_back(std::min(cand[0] - cand[1], cand[0] - cand[2]));
    }

    int pos = -1;
    for (int i = 0; i < 3; ++i) {
        if (count[i] > n / 2) {
            pos = i;
        }
    }

    if (pos >= 0) {
        std::sort(d[pos].begin(), d[pos].end());
        ans -= std::accumulate(d[pos].begin(), d[pos].begin() + count[pos] - n / 2, 0LL);
    }

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