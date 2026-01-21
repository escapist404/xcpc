#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <utility>

const bool CSP[5][9] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1}, 
    {1, 0, 0, 1, 0, 0, 1, 0, 1}, 
    {1, 0, 0, 1, 1, 1, 1, 1, 0}, 
    {1, 0, 0, 0, 0, 1, 1, 0, 0}, 
    {1, 1, 1, 1, 1, 1, 1, 0, 0}
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, L;
    std::cin >> n >> L;

    std::vector<std::vector<int>> mat(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> mat[i][j];
        }
    }

    std::vector<int> d(L + 1);
    for (int x = 0; x <= n - 5; ++x) {
        for (int y = 0; y <= n - 9; ++y) {
            int l = -1, r = L + 1;
            for (int u = 0; u < 5; ++u) {
                for (int v = 0; v < 9; ++v) {
                    if (CSP[u][v] == true) {
                        r = std::min(r, mat[x + u][y + v]);
                    } else {
                        l = std::max(l, mat[x + u][y + v] + 1);
                    }
                }
            }
            if (l <= r) {
                d[l]++;
                d[r + 1]--;
            }
        }
    }

    for (int i = 0; i < L; ++i) {
        if (d[i] > 0) {
            std::cout << i << "\n";
        }
        d[i + 1] += d[i];
    }

    // for (int cand = 0; cand < L; ++cand) {
    //     bool showed = false;
    //     for (int x = 0; x <= n - 5; ++x) {
    //         for (int y = 0; y <= n - 9; ++y) {
    //             bool ok = true;
    //             for (int u = 0; u < 5; ++u) {
    //                 for (int v = 0; v < 9; ++v) {
    //                     bool bi = (mat[x + u][y + v] >= cand);
    //                     if (bi != CSP[u][v]) {
    //                         ok = false;
    //                     }
    //                 }
    //             }
    //             showed |= ok;
    //         }
    //     }
    //     if (showed) {
    //         std::cout << cand << "\n";
    //     }
    // }

    return 0;
}