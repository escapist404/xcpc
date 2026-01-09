#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    std::string T;
    std::cin >> T;

    using ui64 = unsigned long long;
    const int P = 998244353;

    std::vector<ui64> table(n * 26);
    std::mt19937_64 rnd(time(0));
    for (int i = 0; i < n * 26; ++i) {
        table[i] = rnd();
    }

    auto hash = [&](const int S) {
        ui64 h = 0;
        int c = 0;
        for (int i = 0; i < n; ++i) {
            if ((S >> i) & 1) {
                h ^= table[c * 26 + T[i] - 'a'];
                ++c;
            }
        }
        return h;
    };

    std::vector<int> f(1 << n);
    f[0] = 1;

    for (int S = 1; S < 1 << n; ++S) {
        ui64 g = 0, h = hash(S - (S & (-S)));
        std::vector<ui64> to;
        std::vector<int> bit;
        for (int i = 0; i < n; ++i) {
            if ((S >> i) & 1) {
                bit.push_back(i);
            }
        }
        int c = 0;
        for (int j = 0; j < (int)bit.size(); ++j) {
            ui64 t = g ^ h;
            if (std::find(to.begin(), to.end(), t) == to.end()) {
                to.push_back(t);
                (f[S] += f[S ^ (1 << bit[j])]) %= P;
            }
            g ^= table[c * 26 + T[bit[j]] - 'a'];
            if (j < (int)bit.size() - 1) {
                h ^= table[c * 26 + T[bit[j + 1]] - 'a'];
            }
            ++c;
        }
    }

    std::cout << f[(1 << n) - 1] << "\n";
}
