#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;

    bool ok = false;
    ok |= s.find("**") != std::string::npos;
    ok |= s.find("*<") != std::string::npos;
    ok |= s.find(">*") != std::string::npos;
    ok |= s.find("><") != std::string::npos;

    if (ok) {
        std::cout << "-1\n";
        return;
    }

    int c1 = std::count(s.begin(), s.end(), '<') + std::count(s.begin(), s.end(), '*');
    int c2 = std::count(s.begin(), s.end(), '>') + std::count(s.begin(), s.end(), '*');

    std::cout << std::max(c1, c2) << "\n";
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
