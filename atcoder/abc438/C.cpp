#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> s;
    int m = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        s.push_back(x);
        m++;

        if (m >= 4) {
            if (s[m - 4] == s[m - 3] && s[m - 3] == s[m - 2] && s[m - 2] == s[m - 1]) {
                s.erase(s.end() - 4, s.end());
                m -= 4;
            }
        }
    }

    std::cout << s.size() << "\n";
    return 0;
}
