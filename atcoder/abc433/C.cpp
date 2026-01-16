#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

int main() {
    std::string s;
    std::cin >> s;

    int n = s.size();
    std::vector<int> l(n, -1), r(n, n);

    {
        int last = -1;
        for (int i = 0; i < n; ++i) {
            if (last == -1 || s[last] != s[i]) {
                last = i;
            }
            l[i] = last;
        }

        last = n;
        for (int i = n - 1; i >= 0; --i) {
            if (last == n || s[last] != s[i]) {
                last = i;
            }
            r[i] = last;
        }
    }
    
    i64 ans = 0;
    for (char c = '0'; c < '9'; ++c) {
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == c && s[i + 1] == c + 1) {
                int lb = i - l[i] + 1;
                int rb = r[i + 1] - i;
                ans += std::min(lb, rb);
            }
        }
    }

    std::cout << ans << "\n";

    return 0;
}
