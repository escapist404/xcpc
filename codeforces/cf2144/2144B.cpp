#include <bits/stdc++.h>

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        []() {
            int n;
            std::cin >> n;

            std::vector<int> p(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> p[i];
            }

            if (std::count(p.begin(), p.end(), 0) <= 1) {
                auto s = std::set<int>(p.begin(), p.end());
                int v = -1;
                for (int i = 1; i <= n; ++i) {
                    if (s.count(i) == 0) {
                        v = i;
                        break;
                    }
                }
                if (v != -1) {
                    *std::find(p.begin(), p.end(), 0) = v;
                }
            }
            
            std::vector<int> pos;
            for (int i = 0; i < n; ++i) {
                if (p[i] != i + 1) {
                    pos.push_back(i);
                }
            }
            if (pos.size() == 0) {
                std::cout << 0 << "\n";
            } else {
                std::cout << pos.back() - pos.front() + 1 << "\n";
            }
        }();
    }
}
