#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;
    
    int c[] = {std::count(s.begin(), s.end(), '0'), std::count(s.begin(), s.end(), '1')};
    int ans = 1e9;
    for (int i = 0, j = 0; i < n; i = j) {
        while (j < n && s[j] == s[i]) {
            ++j;
        }   
        ans = std::min(ans, 2 * (c[s[i] - '0'] - (j - i)) + c[(s[i] - '0') ^ 1]);
    }

    std::cout << ans << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}