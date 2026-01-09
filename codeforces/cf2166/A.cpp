#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    
    std::cout << n - 1 - std::count(s.begin(), s.end() - 1, s.back()) << "\n";
}

int main() {
    int T;
    std::cin >> T;
    
    while (T--) {
        solve();
    }
    
    return 0;
}
