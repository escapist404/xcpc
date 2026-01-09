#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    std::vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            ans.push_back(i);
        }
    }

    std::cout << ans.size() << "\n";
    for (auto i : ans) {
        std::cout << i + 1 << " ";
    }
    std::cout << "\n";
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}