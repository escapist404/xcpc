#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;
            std::string s;
            std::cin >> s;
            int c = std::count(s.begin(), s.end(), '1');

            int ans = 0;
            for (int i = n - c; i < n; ++i) {
                if (s[i] == '0') {
                    ++ans;
                }
            }

            std::cout << ans << "\n";
        }();
    }
}
