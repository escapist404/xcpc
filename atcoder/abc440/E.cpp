#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>

using i64 = long long;

int main() {
    int n, k, x;
    std::cin >> n >> k >> x;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::sort(a.begin(), a.end(), std::greater<int>());
    std::set<std::pair<i64, std::vector<int>>, std::greater<std::pair<i64, std::vector<int>>>> set;
    std::vector<int> base(n);
    base[0] = k;
    set.emplace(1LL * a[0] * k, base);

    int ans = 0;
    std::set<std::vector<int>> chosen;
    while (ans < x) {
        auto [score, way] = *set.begin();
        set.erase(set.begin());
        if (chosen.count(way) == false) {
            std::cout << score << "\n";
            chosen.insert(way);
            ++ans;
            for (int i = 0; i < n - 1; ++i) {
                if (way[i] > 0) {
                    way[i]--;
                    way[i + 1]++;
                    score += a[i + 1] - a[i];
                    set.emplace(score, way);
                    score -= a[i + 1] - a[i];
                    way[i + 1]--;
                    way[i]++;
                }
            }
        }
    }

    return 0;
}
