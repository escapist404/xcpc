#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::string s, t;
    std::cin >> s >> t;

    int ans = 1E9;
    for (int i = 0; i <= n - m; ++i) {
        int cur = 0;
        for (int j = 0; j < m; ++j) {
            cur += ((int)s[i + j] - (int)t[j] + 10) % 10;
        }
        ans = std::min(ans, cur);
    }

    std::cout << ans << "\n";
}
