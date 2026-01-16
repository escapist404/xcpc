#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> x(n), y(m);
    std::vector<std::pair<int, int>> t(n * m, {-1, -1});
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i];
        --x[i];
        t[x[i]].first = i;
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> y[i];
        --y[i];
        t[y[i]].second = i;
    }

    std::vector<std::vector<int>> mat(n, std::vector<int>(m));
    std::vector<std::vector<int>> sgn(n, std::vector<int>(m));
    std::vector<std::vector<int>> rfill(n);
    std::vector<std::vector<int>> cfill(m);

    std::vector<std::pair<int, int>> b;
    for (int i = n * m - 1; i >= 0; --i) {
        auto [r, c] = t[i];
        if (r == -1 && c == -1) {
            if (b.empty()) {
                std::cout << "No\n";
                return;
            }

            mat[b.back().first][b.back().second] = i;
            sgn[b.back().first][b.back().second] = 4;

            b.pop_back();
        } else if (r != -1 && c == -1) {
            if (rfill[r].empty()) {
                std::cout << "No\n";
                return;
            }

            int g = rfill[r].back();
            mat[r][g] = i;
            sgn[r][g] = 4;
            rfill[r].clear();

            for (int j = 0; j < m; ++j) {
                if (sgn[r][j] == 0) {
                    sgn[r][j] = 2;
                    cfill[j].push_back(r);
                } else if (sgn[r][j] == 1) {
                    sgn[r][j] = 3;
                    b.push_back({r, j});
                }
            }
        } else if (r == -1 && c != -1) {
            if (cfill[c].empty()) {
                std::cout << "No\n";
                return;
            }
             
            int g = cfill[c].back();
            mat[g][c] = i;
            sgn[g][c] = 4;
            cfill[c].clear();

            for (int j = 0; j < n; ++j) {
                if (sgn[j][c] == 0) {
                    sgn[j][c] = 1;
                    rfill[j].push_back(c);
                } else if (sgn[j][c] == 2) {
                    sgn[j][c] = 3;
                    b.push_back({j, c});
                }
            }
        } else {
            if (sgn[r][c] != 0) {
                std::cout << "No\n";
                return;
            }

            mat[r][c] = i;
            sgn[r][c] = 4;
            
            for (int j = 0; j < m; ++j) {
                if (sgn[r][j] == 0) {
                    sgn[r][j] = 2;
                    cfill[j].push_back(r);
                } else if (sgn[r][j] == 1) {
                    sgn[r][j] = 3;
                    b.push_back({r, j});
                }
            }

            for (int j = 0; j < n; ++j) {
                if (sgn[j][c] == 0) {
                    sgn[j][c] = 1;
                    rfill[j].push_back(c);
                } else if (sgn[j][c] == 2) {
                    sgn[j][c] = 3;
                    b.push_back({j, c});
                }
            }
        }
    }

    std::cout << "Yes\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << mat[i][j] + 1 << " \n"[j == m - 1];
        }
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
