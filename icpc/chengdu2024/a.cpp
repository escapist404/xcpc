#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string S;
    std::cin >> S;

    int n = S.size();
    if (S[0] != '>' || S.substr(n - 3, 3) != ">>>" || S.find('-') == S.npos) {
        std::cout << "No\n";
        return;
    }

    std::vector<std::pair<int, int>> ans;
    int x = n - 3;
    while (x >= 0 && S[x] == '>') {
        x--;
    }
    ++x;
    
    for (int i = n; i > x + 3; --i) {
        ans.emplace_back(i - 5, 5);
    }
    for (int i = 0; i <= x - 2; ++i) {
        if (S[i] == '>') {
            ans.emplace_back(i, x + 3 - i);
        }
    }

    std::cout << "Yes " << ans.size() << "\n";
    for (auto [x, y] : ans) {
        std::cout << x + 1 << " " << y << "\n";
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
