#include <bits/stdc++.h>

const int base1[3][6] = {{0, 2, 2, 1, 1, 0},
                         {2, 0, 1, 2, 0, 1},
                         {1, 1, 0, 0, 2, 2}};

const int base2[6][6] = {{0, 2, 1, 1, 2, 0},
                         {2, 0, 1, 1, 0, 2},
                         {2, 1, 0, 0, 1, 2},
                         {1, 2, 0, 0, 2, 1},
                         {1, 0, 2, 2, 0, 1},
                         {0, 1, 2, 2, 1, 0}};

void solve() {
    int n, m;
    std::cin >> n >> m;

    bool mirrored = false;
    bool ok = true;
    if (n % 3 != 0) {
        std::swap(n, m);
        mirrored = true;
    }

    std::vector<std::vector<int>> P(n, std::vector<int>(m));
    if (m <= 2) {
        if (n >= 9) {
            ok = false;
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    P[i][j] = i / (n / 3);
                }
            }
        }
    } else if (n == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                P[i][j] = base1[i % 3][j % 6];
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                P[i][j] = base2[i % 6][j % 6];
            }
        }
        if (m % 3 == 1 && n / 3 % 2 == 1) {
            if (m / 3 % 2 == 1) {
                P[0][2] = 2;
            } else {
                P[n - 1][0] = 1;
            }
        }
        if (m % 3 == 2) {
            if (n % 2 == 0) {
                if (m % 2 != 0) {
                    P[0][m / 3 * 3 - 1] = 2;
                    P[0][m / 3 * 3 + 1] = 1;
                    P[n - 1][m / 3 * 3 - 1] = 1;
                    P[n - 1][m / 3 * 3 + 1] = 2;
                }
            } else if (n / 3 % 2 == 1) {
                if (m / 3 % 2 == 1) {
                    P[0][m / 3 * 3 - 1] = 2;
                    P[0][m / 3 * 3 + 1] = 1;
                    P[2][m - 1] = 2;
                } else {
                    P[n - 1][m / 3 * 3 - 1] = 1;
                    P[n - 1][m / 3 * 3 + 1] = 2;
                    P[n - 3][m - 1] = 1;
                }
            } else {
                if (m / 3 % 2 == 1) {
                    P[0][m / 3 * 3 - 1] = 2;
                    P[0][m / 3 * 3 + 1] = 1;
                    P[n - 1][m / 3 * 3 - 1] = 1;
                }
            }
        }
    }

    if (ok) {
        std::cout << "Yes\n";
        if (mirrored) {
            for (int j = 0; j < m; ++j) {
                for (int i = 0; i < n; ++i) {
                    std::cout << P[i][j];
                }
                std::cout << "\n";
            }
        } else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    std::cout << P[i][j];
                }
                std::cout << "\n";
            }
        }
    } else {
        std::cout << "No\n";
    }

    if (ok) {
        int count[3] = {0, 0, 0};
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                count[P[i][j]]++;
            }
        }

        std::vector<int> par(n * m);
        std::iota(par.begin(), par.end(), 0);

        auto get = [&](auto& self, int x) -> int {
            return par[x] == x ? x : par[x] = self(self, par[x]);
        };

        auto isconnected = [&](int x, int y) {
            return get(get, x) == get(get, y);
        };

        auto connect = [&](int x, int y) {
            if (isconnected(x, y)) {
                return false;
            }
            x = get(get, x);
            y = get(get, y);
            par[x] = y;
            return true;
        };

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m - 1; ++j) {
                if (P[i][j] == P[i][j + 1]) {
                    connect(i * m + j, i * m + j + 1);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m - 1; ++j) {
                if (P[i][j] == P[i][j + 1]) {
                    connect(i * m + j, i * m + j + 1);
                }
            }
        }
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < m; ++j) {
                if (P[i][j] == P[i + 1][j]) {
                    connect((i + 1) * m + j, i * m + j);
                }
            }
        }
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < m - 1; ++j) {
                if (P[i][j] == P[i + 1][j + 1]) {
                    connect(i * m + j, (i + 1) * m + j + 1);
                }
            }
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < m - 1; ++j) {
                if (P[i][j] == P[i - 1][j + 1]) {
                    connect(i * m + j, (i - 1) * m + j + 1);
                }
            }
        }

        int set_counter = 0;
        for (int i = 0; i < n * m; ++i) {
            if (get(get, i) == i) {
                ++set_counter;
            }
        }

        bool vec = false, hor = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m - 2; ++j) {
                if (P[i][j] == P[i][j + 1] && P[i][j] == P[i][j + 2]) {
                    vec = true;
                }
            }
        }
        for (int i = 0; i < n - 2; ++i) {
            for (int j = 0; j < m; ++j) {
                if (P[i][j] == P[i + 1][j] && P[i][j] == P[i + 2][j]) {
                    hor = true;
                }
            }
        }

        assert(count[0] == count[1] && count[1] == count[2]);
        assert(set_counter == 3);
        assert(vec == false);
        assert(hor == false);
    }
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}