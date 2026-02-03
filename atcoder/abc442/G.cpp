#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

const int W = 3;
using i64 = long long;

int main() {
    int n, c;
    std::cin >> n >> c;

    std::vector<std::vector<std::pair<i64, int>>> it(W + 1);
    i64 it_cnt[] = {0, 0, 0, 0};
    for (int i = 0; i < n; ++i) {
        int cw, ck;
        i64 cv;
        std::cin >> cw >> cv >> ck;
        it[cw].emplace_back(cv, ck);
        it_cnt[cw] += ck;
    }

    for (auto& s : it) {
        std::sort(s.begin(), s.end());
    }

    std::vector<std::vector<std::pair<i64, std::vector<std::pair<i64, int>>>>> grp(W + 1);
    for (int i = 1; i <= 3; ++i) {
        int g = 6 / i;
        grp[i].resize(g);
        for (int s = 0; s < g; ++s) {
            int t = s;
            auto lst = it[i];
            auto& [now, res] = grp[i][s];
            while (t > 0 && lst.empty() == false) {
                auto& [v, k] = lst.back();
                int d = std::min(t, k);
                t -= d;
                k -= d;
                now += 1LL * v * d;
                if (k == 0) {
                    lst.pop_back();
                } else {
                    break;
                }
            }
            std::vector<int> tmp;
            while (lst.empty() == false) {
                auto& [v, k] = lst.back();
                if (tmp.empty() == false) {
                    while ((int)tmp.size() < g && k > 0) {
                        tmp.push_back(v);
                        --k;
                    }
                    if ((int)tmp.size() == g) {
                        res.emplace_back(std::accumulate(tmp.begin(), tmp.end(), 0LL), 1);
                        tmp.clear();
                    }
                }
                if (k >= g) {
                    res.emplace_back(1LL * v * g, k / g);
                }
                k -= k / g * g;
                while (k > 0) {
                    tmp.push_back(v);
                    --k;
                }
                lst.pop_back();
            }
            std::reverse(res.begin(), res.end());
        }
    }

    i64 ans = 0;
    for (int r = 0; r < 36; ++r) {
        int s[] = {0, r / 6, r % 6 / 2, r % 2};
        if (s[1] + 2 * s[2] + 3 * s[3] > c || s[1] > it_cnt[1] || s[2] > it_cnt[2] || s[3] > it_cnt[3]) {
            continue;
        }
        s[0] = (c - s[1] - 2 * s[2] - 3 * s[3]) / 6;

        i64 total_v = 0;
        std::vector<std::pair<i64, int>> mrg;
        for (int i = 1; i <= 3; ++i) {
            auto& [now, res] = grp[i][s[i]];
            mrg.insert(mrg.end(), res.begin(), res.end());
            std::inplace_merge(mrg.begin(), mrg.end() - res.size(), mrg.end());
            total_v += now;
        }

        while (s[0] > 0 && mrg.empty() == false) {
            auto& [v, k] = mrg.back();
            int d = std::min(s[0], k);
            s[0] -= d;
            k -= d;
            total_v += 1LL * v * d;
            if (k == 0) {
                mrg.pop_back();
            } else {
                break;
            }
        }

        ans = std::max(ans, total_v);
    }

    std::cout << ans << "\n";
    return 0;
}
