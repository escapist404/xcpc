#include <bits/stdc++.h>

int main() {
    std::string s;
    std::cin >> s;

    int n = s.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int k = j - i + j;
            if (k >= n) {
                continue;
            }

            ans += (s[i] == 'A' && s[j] == 'B' && s[k] == 'C');
        }
    }

    std::cout << ans << "\n";
    return 0;
}
