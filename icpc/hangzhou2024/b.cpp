#include <bits/stdc++.h>

using i64 = long long;

const int N = 1000000, S = 63;

std::array<std::bitset<N>, S> T;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    
    int n, q;
    std::cin >> n >> q;

    for (int i = 0; i < n; ++i) {
        i64 x;
        std::cin >> x;
        for (int j = 0; j < S; ++j) {
            T[j][i] = (x >> j) & 1;
        }
    }

    while (q--) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int l, r;
            i64 x;
            std::cin >> l >> r >> x;
            --l;

            for (int j = 0; j < S; ++j) {
                if ((x >> j) & 1) {
                    continue;
                }
                for (int k = l; k < r; ++k) {
                    T[j][k] = 0;
                }
            }
        } else if (type == 2) {
            int s;
            i64 x;
            std::cin >> s >> x;
            --s;

            for (int j = 0; j < S; ++j) {
                T[j][s] = (x >> j) & 1;
            }
        } else {
            int l, r;
            std::cin >> l >> r;
            --l;

            i64 ans = 0;
            int s = -1;
            for (int j = S - 1; j >= 0; --j) {
                int c = (T[j] >> l).count() - (T[j] >> r).count();
                if (c == r - l) {
                    ans ^= 1LL << j;
                } else if (c == r - l - 1) {
                    int t = (~T[j] >> l)._Find_first() + l;
                    if (s == -1) {
                        s = t;
                    }
                    if (s == t) {
                        ans ^= 1LL << j;
                    }
                }
            }

            std::cout << ans << "\n";
        }
    }
}
