#include <bits/stdc++.h>

using i64 = long long;

int main() {
    int n;
    std::cin >> n;

    std::set<int> s = {0};
    std::map<int, int> d = {{0, 1E9}};
    i64 ans = 1E9;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        auto next = s.upper_bound(x);
        auto prev = std::prev(s.lower_bound(x));

        int min = x - *prev;
        if (next != s.end()) {
            min = std::min(min, *next - x);
        }

        d[x] = min;
        ans += min;
        
        ans -= d[*prev];
        d[*prev] = std::min(d[*prev], x - *prev);
        ans += d[*prev];

        if (next != s.end()) {
            ans -= d[*next];
            d[*next] = std::min(d[*next], *next - x);
            ans += d[*next];
        }

        s.insert(x);

        std::cout << ans << "\n";
    }

    return 0;
}