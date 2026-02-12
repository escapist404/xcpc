#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <queue>

using i64 = long long;
const int P = 1000000007;

int main() {
    int n;
    std::cin >> n;

    std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<std::pair<i64, int>>> pq;
    for (int i = 0; i < n; ++i) {
        int c, w;
        std::cin >> c >> w;
        pq.emplace(w, c);
    }

    int ans = 0;
    while (pq.empty() == false) {
        auto [w, c] = pq.top();
        pq.pop();
        if (c == 1) {
            if (pq.empty()) {
                break;
            }
            auto [w1, c1] = pq.top();
            pq.pop();
            (ans += (w + w1) % P) %= P;
            pq.emplace(w + w1, 1);
            if (c1 - 1 != 0) {
                pq.emplace(w1, c1 - 1);
            }
        } else {
            (ans += 1LL * (2 * w) % P * (c / 2) % P) %= P;
            pq.emplace(2 * w, c / 2);
            if (c % 2 == 1) {
                pq.emplace(w, 1);
            }
        }
    }

    std::cout << ans << "\n";

    return 0;
}
