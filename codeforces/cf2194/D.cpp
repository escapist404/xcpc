#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> s(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> s[i][j];
        }
    }

    int d = 0;
    for (int i = 0; i < n; ++i) {
        d += std::accumulate(s[i].begin(), s[i].end(), 0);
    }

    int lo = d / 2;
    int hi = d - lo;
    i64 ans = 1LL * lo * hi;
    int now = 0;
    std::string op;
    for (int i = 0; i < n; ++i) {
        int c = std::accumulate(s[i].begin(), s[i].end(), 0);
        if (now + c <= lo) {
            now += c;
            op += "D";
        } else {
            for (int j = 0; j < m; ++j) {
                if (now + c > lo) {
                    op += "R";
                    c -= s[i][j];
                } else {
                    op += "D";
                    break;
                }
            }
            break;
        }
    }
    op += std::string(m - std::count(op.begin(), op.end(), 'R'), 'R');
    op += std::string(n - std::count(op.begin(), op.end(), 'D'), 'D');

    std::cout << ans << "\n" << op << "\n";
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
