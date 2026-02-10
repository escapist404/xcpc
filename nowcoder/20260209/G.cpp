#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // i64 l, r;
    // std::cin >> l >> r;

    // auto f = [](i64 v) {
    //     i64 r = 1;
    //     do {
    //         r *= v % 10;
    //         v /= 10;
    //     } while (v);
    //     return r;
    // };

    // auto g = [f](i64 v) {
    //     int c = 0;
    //     while (true) {
    //         i64 r = f(v);
    //         if (r == v) {
    //             break;
    //         }
    //         c++;
    //         v = r;
    //     }
    //     return c;
    // };

    // int m = -1;
    // std::vector<i64> b;

    // int p[] = {2, 3, 4, 5, 6, 7, 8, 9};
    // int c[] = {0, 0, 0, 0, 0, 0, 0, 0};

    // auto vd = [&]() {
    //     return (c[0] + c[1] + c[2] + c[3] + c[4] + c[5] + c[6] + c[7]) <= 17;
    // };

    // for (c[0] = 0; vd(); ++c[0]) {
    //     for(c[1] = 0; vd(); ++c[1]) {
    //         for (c[2] = 0; vd(); ++c[2]) {
    //             for (c[3] = 0; vd(); ++c[3]) {
    //                 for (c[4] = 0; vd(); ++c[4]) {
    //                     for (c[5] = 0; vd(); ++c[5]) {
    //                         for (c[6] = 0; vd(); ++c[6]) {
    //                             for (c[7] = 0; vd(); ++c[7]) {
    //                                 i64 v = 0;
    //                                 for (int k = 0; k < 8; ++k) {
    //                                     for (int l = 0; l < c[k]; ++l) {
    //                                         v *= 10;
    //                                         v += p[k];
    //                                     }
    //                                 }
    //                                 i64 gv = g(v);
    //                                 if (gv > m) {
    //                                     b.clear();
    //                                     b.push_back(v);
    //                                     m = gv;
    //                                 } else if (gv == m) {
    //                                     b.push_back(v);
    //                                 }
    //                             }
    //                             c[7] = 0;
    //                         }
    //                         c[6] = 0;
    //                     }
    //                     c[5] = 0;
    //                 }
    //                 c[4] = 0;
    //             }
    //             c[3] = 0;
    //         }
    //         c[2] = 0;
    //     }
    //     c[1] = 0;
    // }
    // c[0] = 0;

    // std::cout << m << " " << b.size() << "\n";
    // for (auto i : b) {
    //     std::cout << i << " " << f(i) << "\n";
    // }

    std::cout << 66667777799999999 << " " << 666677777788888 << "\n";

    return 0;
}

// 66667777799999999 666677777788888
// 
