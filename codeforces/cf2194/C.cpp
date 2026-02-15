#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;
const int S = 26;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::string> s(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> s[i];
    }

    std::vector<int> div;
    for (int d = 1; d * d <= n; ++d) {
        if (n % d == 0) {
            div.push_back(d);
            if (n / d != d) {
                div.push_back(n / d);
            }
        }
    }
    std::sort(div.begin(), div.end());

    for (const auto d : div) {
        std::string ans(d, '?');
        bool ok = true;
        for (int i = 0; i < d; ++i) {
            int c = (1 << S) - 1;
            for (int j = 0; j * d + i < n; ++j) {
                int p = 0;
                for (int u = 0; u < k; ++u) {
                    p |= 1 << (s[u][j * d + i] - 'a');
                }
                c &= p;
            }
            if (c != 0) {
                c = c & -c;
                for (int u = 0; u < S; ++u) {
                    if (c == (1 << u)) {
                        ans[i] = 'a' + u;
                        break;
                    }
                }
            } else {
                ok = false;
                break;
            }
        }
        if (ok) {
            for (int u = 0; u < n / d; ++u) {
                std::cout << ans;
            }
            std::cout << "\n";
            break;
        }
    }
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
