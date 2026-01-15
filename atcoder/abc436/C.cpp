#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

int main() {
    int n, m;
    std::cin >> n >> m;

    int ans = 0;
    std::set<std::pair<int, int>> set;
    for (int i = 0; i < m; ++i) {
        int r, c;
        std::cin >> r >> c;
        --r, --c;
        if (set.contains({r, c}) || set.contains({r + 1, c}) || set.contains({r, c + 1}) || set.contains({r + 1, c + 1})) {
            continue;
        }
        ans++;
        set.emplace(r, c);
        set.emplace(r + 1, c);
        set.emplace(r, c + 1);
        set.emplace(r + 1, c + 1);
    }

    std::cout << ans << "\n";
    return 0;
}
