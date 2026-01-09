#include <bits/stdc++.h>

const std::pair<int, int> d[] = {std::make_pair(-1, 0), std::make_pair(1, 0), std::make_pair(0, -1), std::make_pair(0, 1)};

int main() {
    int h, w;
    std::cin >> h >> w;

    std::vector<std::string> map(h);
    for (int i = 0; i < h; ++i) {
        std::cin >> map[i];
    }

    auto valid = [&](int x, int y) {
        return 0 <= x && x < h && 0 <= y && y < w;
    };

    std::queue<std::pair<int, int>> cur, next;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (map[i][j] == '#') {
                for (auto [dx, dy] : d) {
                    if (valid(i + dx, j + dy) && map[i + dx][j + dy] == '.') {
                        cur.push({i + dx, j + dy});
                    }
                }
            }
        }
    }

    while (cur.empty() == false) {
        std::vector<std::pair<int, int>> confirmed;
        while (cur.empty() == false) {
            auto [x, y] = cur.front();
            cur.pop();
            
            if (map[x][y] == '#') {
                continue;
            }   
            
            int c = 0;
            for (auto [dx, dy] : d) {
                if (valid(x + dx, y + dy) && map[x + dx][y + dy] == '#') {
                    ++c;
                }
            }

            if (c == 1) {
                confirmed.push_back({x, y});
                for (auto [dx, dy] : d) {
                    if (valid(x + dx, y + dy) && map[x + dx][y + dy] == '.') {
                        next.push({x + dx, y + dy});
                    }
                }
            }
        }
        std::swap(next, cur);
        for (auto [x, y] : confirmed) {
            map[x][y] = '#';
        }
    }

    int ans = 0;
    for (int i = 0; i < h; ++i) {
        ans += std::count(map[i].begin(), map[i].end(), '#');
    }

    std::cout << ans << "\n";
}