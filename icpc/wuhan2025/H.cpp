#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
#include <map>
#include <set>
#include <unordered_set>

int counter = 0;

namespace interactor {
int ask(int c) {
    counter++;
    std::cout << "? " << c << "\n";
    std::cout << std::flush;
    int ret;
    std::cin >> ret;
    return ret;
}
void report(const std::unordered_set<int>& ans) {
    std::cout << "!";
    for (auto i : ans) {
        std::cout << " " << i;
    }
    std::cout << "\n";

    std::cout << std::flush;
}
}

const int U = (1 << 30) - 1;

void solve() {
    counter = 0;

    int n;
    std::cin >> n;
    
    std::unordered_set<int> ans;
    auto find = [&](auto& self, int min, int max) {
        if (counter == 2 * n - 2) {
            return;
        }
        if (ans.size() == n) {
            return;
        }
        if (min > max) {
            return;
        }

        int cmin, cmax;

        {
            int diff = max ^ min;
            int idx = std::__lg(diff);
            int same = min >> (idx + 1) << (idx + 1);
    
            int qmin = U ^ same;
            int qmax = U ^ same ^ ((1 << (idx + 1)) - 1);

            if (ans.count(min) == 0) {
                cmin = interactor::ask(qmin) ^ qmin;
            } else {
                cmin = min;
            }

            if (ans.count(max) == 0) {
                cmax = interactor::ask(qmax) ^ qmax;
            } else {
                cmax = max;
            }
        }

        if (cmin == cmax) {
            ans.insert(cmin);
            return;
        } else {
            ans.insert(cmin);
            ans.insert(cmax);
        }

        int cdiff = cmax ^ cmin;
        int cidx = std::__lg(cdiff);
        int csame = cmin >> cidx << cidx;

        self(self, cmin, (csame ^ (1 << cidx)) - 1);
        self(self, (csame ^ (1 << cidx)), cmax);
    };

    find(find, 0, U);
    interactor::report(ans);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}