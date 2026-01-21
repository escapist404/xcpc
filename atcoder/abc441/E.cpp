#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using i64 = long long;

int main() {
    int n;
    std::string s;
    std::cin >> n >> s;

    auto find_interval = [&](auto& self, int l, int r) -> i64 {
        if (r - l == 1) {
            return s[l] == 'A';
        }
        int m = r - l;
        int p = (l + r) / 2;
        i64 lans = self(self, l, p);
        i64 rans = self(self, p, r);
        i64 cans = 0;

        std::vector<int> rfix(r - p);
        for (int i = p, v = 0; i < r; ++i) {
            if (s[i] == 'A') {
                v++;
            } else if (s[i] == 'B') {
                v--;
            }
            rfix[i - p] = v;
        }

        int rfmin = *std::min_element(rfix.begin(), rfix.end());
        int rfmax = *std::max_element(rfix.begin(), rfix.end());
        std::vector<int> rcount(rfmax - rfmin + 1);
        for (int i = 0; i < r - p; ++i) {
            rcount[rfix[i] - rfmin]++;
        }
        for (int i = rfmax - rfmin - 1; i >= 0; --i) {
            rcount[i] += rcount[i + 1];
        }

        for (int i = p - 1, v = 0; i >= l; --i) {
            if (s[i] == 'A') {
                v++;
            } else if (s[i] == 'B') {
                v--;
            }
            int f = std::max(-(v + rfmin) + 1, 0);
            if (f > rfmax - rfmin) {
                continue;
            }
            cans += rcount[f];
        }

        return lans + cans + rans;
    };

    std::cout << find_interval(find_interval, 0, n) << "\n";

    return 0;
}
