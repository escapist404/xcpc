#include <bits/stdc++.h>

using i64 = long long;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::set<int> S = {0};
    int x;
    std::cin >> x;
    for (int i = 1; i < n; ++i) {
        int y;
        std::cin >> y;
        S.insert(x);
        S.insert(y);
        S.insert(x ^ y);
        S.insert(x & y);
        S.insert(x | y);
        S.insert(x & (x ^ y));
        S.insert(y & (x ^ y));
        x = y;
    }

    std::cout << S.size() << "\n";

    return 0;
}
