#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> absolute(n);
    for (auto& [orient, len] : absolute) {
        char o;
        std::cin >> o >> len;
        if (o == 'N') {
            orient = 0;
        } else if (o == 'E') {
            orient = 1;
        } else if (o == 'S') {
            orient = 2;
        } else {
            orient = 3;
        }
    }

    std::vector<std::pair<char, int>> respective;
    int cur_orient = absolute.front().first;
    for (auto [orient, len] : absolute) {
        if (orient == ((cur_orient + 1) & 3)) {
            respective.emplace_back('R', 0);
        } else if (cur_orient == ((orient + 1) & 3)) {
            respective.emplace_back('L', 0);
        }
        cur_orient = orient;
        respective.emplace_back('Z', len);
    }

    std::cout << respective.size() << " " << "NESW"[absolute.front().first] << "\n";
    for (auto [g, y] : respective) {
        std::cout << g;
        if (g == 'Z') {
            std::cout << " " << y;
        }
        std::cout << "\n";
    }
}

int main() {
    int tt;
    std::cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
