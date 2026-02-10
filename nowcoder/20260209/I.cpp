#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // int best[6];
    // i64 max = -1;
    // int g[6], c[7] {};
    // for (g[0] = 0; g[0] <= 6; ++g[0]) {
    //     for (g[1] = 0; g[1] <= 6; ++g[1]) {
    //         for (g[2] = 0; g[2] <= 6; ++g[2]) {
    //             for (g[3] = 0; g[3] <= 6; ++g[3]) {
    //                 for (g[4] = 0; g[4] <= 6; ++g[4]) {
    //                     for (g[5] = 0; g[5] <= 6; ++g[5]) {
    //                         for (int i = 0; i < 6; ++i) {
    //                             c[g[i]]++;
    //                         }
    //                         i64 score = 0;
    //                         int x[3], o[6] {};
    //                         for (x[0] = 0; x[0] < 6; ++x[0]) {
    //                             o[x[0]]++;
    //                             for (x[1] = 0; x[1] < 6; ++x[1]) {
    //                                 o[x[1]]++;
    //                                 for (x[2] = 0; x[2] < 6; ++x[2]) {
    //                                     o[x[2]]++;
    //                                     for (int i = 0; i < 6; ++i) {
    //                                         if (o[i] == 1) {
    //                                             score += 2 * c[i];
    //                                         }
    //                                         if (o[i] == 2) {
    //                                             score += 3 * c[i];
    //                                         }
    //                                         if (o[i] == 3) {
    //                                             score += 10 * c[i];
    //                                         }
    //                                     }
    //                                     score += c[6];
    //                                     o[x[2]]--;
    //                                 }
    //                                 o[x[1]]--;
    //                             }
    //                             o[x[0]]--;
    //                         }
    //                         if (max < score) {
    //                             max = score;
    //                             for (int i = 0; i < 6; ++i) {
    //                                 best[i] = g[i];
    //                             }
    //                         }
    //                         for (int i = 0; i < 6; ++i) {
    //                             c[g[i]]--;
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    // std::cout << max << "\n";
    // for (int i = 0; i < 6; ++i) {
    //     std::cout << "WGBPYO#"[best[i]];
    // }
    // std::cout << "\n";

    std::cout << "######\n";

    return 0;
}
