#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n, m;
    std::string s, t;
    std::cin >> n >> m >> s >> t;

    int q;
    std::cin >> q;
    while (q--) {
        std::string w;
        std::cin >> w;
        bool it = false;
        bool ia = false;
        for (auto c : w) {
            bool fs = s.find(c) != std::string::npos;
            bool ft = t.find(c) != std::string::npos;
            if (fs && !ft) {
                it = true;
            } else if (!fs && ft) {
                ia = true;
            }
        }
        if (it) {
            std::cout << "Takahashi\n";
        } else if (ia) {
            std::cout << "Aoki\n";
        } else {
            std::cout << "Unknown\n";
        }
    }

    return 0;
}
