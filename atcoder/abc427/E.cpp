#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <utility>
#include <queue>

int main() {
    int h, w;
    std::cin >> h >> w;

    int f = -1, g = -1;

    std::vector<std::string> s(h);
    for (int i = 0; i < h; ++i) {
        std::cin >> s[i];
        if (s[i].find('T') != std::string::npos) {
            f = i;
            g = s[i].find('T');
            s[f][g] = '.';
        }
    }

    std::vector<std::vector<int>> t(h + 1, std::vector<int>(w + 1));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            t[i + 1][j + 1] = t[i + 1][j] + (s[i][j] == '#');
        }
    }
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            t[i + 1][j + 1] += t[i][j + 1];
        }
    }

    auto sum = [t](int u, int l, int d, int r) {
        return t[d][r] - t[d][l] - t[u][r] + t[u][l];
    };

    auto id = [h, w](int x, int y, int u, int l, int d, int r) {
        int xy = (x + h) * (2 * w + 1) + y + w;
        int ul = u * (w + 1) + l;
        int dr = d * (w + 1) + r;
        return (xy * (h + 1) * (w + 1) + ul) * (h + 1) * (w + 1) + dr;
    };

    auto dec = [h, w](int id) {
        int xy = id / ((h + 1) * (w + 1) * (h + 1) * (w + 1));
        int ul = id % ((h + 1) * (w + 1) * (h + 1) * (w + 1)) / ((h + 1) * (w + 1));
        int dr = id % ((h + 1) * (w + 1));
        int x = xy / (2 * w + 1) - h;
        int y = xy % (2 * w + 1) - w;
        int u = ul / (w + 1);
        int l = ul % (w + 1);
        int d = dr / (w + 1);
        int r = dr % (w + 1);
        return std::make_tuple(x, y, u, l, d, r);
    };

    const int Z = (2 * h + 1) * (2 * w + 1) * (h + 1) * (w + 1) * (h + 1) * (w + 1);
    const int S = id(0, 0, 0, 0, h, w);
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, 1, 0, -1};

    std::vector<int> dis(Z), vis(Z);
    std::queue<int> queue;
    vis[S] = 1, queue.emplace(S);

    int ans = 1E9;

    while (queue.empty() == false) {
        int c = queue.front();
        queue.pop();
        auto [x, y, u, l, d, r] = dec(c);
        if (sum(u, l, d, r) == 0) {
            ans = std::min(dis[c], ans);
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nu = nx + u < 0 ? u + 1 : u;
            int nl = ny + l < 0 ? l + 1 : l;
            int nd = nx + d > h ? d - 1 : d;
            int nr = ny + r > w ? r - 1 : r;

            int nc = id(nx, ny, nu, nl, nd, nr);
            if (vis[nc]) {
                continue;
            }
            
            int rf = f - nx;
            int rg = g - ny;
            if (rf >= nu && rf < nd && rg >= nl && rg < nr && s[rf][rg] == '#') {
                continue;
            }

            dis[nc] = dis[c] + 1;
            vis[nc] = true;
            queue.emplace(nc);
        }
    }

    std::cout << (ans == 1E9 ? -1 : ans) << "\n";
    return 0;
}
