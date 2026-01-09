#include <bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::string s;
    std::cin >> s;
    
    std::set<int> a;
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        a.insert(x);
    }

    int cur = 1;
    for (int i = 0; i < n; ++i) {
        cur++;
        if (s[i] == 'A') {
            a.insert(cur);
        } else {
            while (a.count(cur) == true) {
                cur++;
            }
            a.insert(cur++);
            while (a.count(cur) == true) {
                cur++;
            }
        }
    }

    std::cout << a.size() << "\n";
    for (const auto i : a) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }
}