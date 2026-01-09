#include <bits/stdc++.h>

using i64 = long long;

int main() {
    int n, a, b;
    std::cin >> n >> a >> b;

    std::string s;
    std::cin >> s;

    i64 ans = 0;
    std::vector<int> occ_a, occ_b;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a') {
            occ_a.push_back(i);
        } else {
            occ_b.push_back(i);
        }

        int pa;
        if (occ_a.size() < a) {
            pa = -1;
        } else {
            pa = occ_a[(int)occ_a.size() - a];
        }
        
        int pb;
        if (occ_b.size() < b) {
            pb = 0;
        } else {
            pb = occ_b[(int)occ_b.size() - b] + 1;
        }

        std::cerr << pa << " " << pb << "\n";
        
        ans += std::max(pa - pb + 1, 0);
    }

    std::cout << ans << "\n";
    return 0;
}